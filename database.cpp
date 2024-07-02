#undef UNICODE
#undef _UNICODE
#include<Windows.h>
#include <sql.h> 
#include <sqlext.h> 
#include<sqltypes.h>
#include<string>
#include <iomanip>
#include <iostream>
#include"database.h"

using namespace std;
//全局常量
const int DATAPERPAGE = 15; //每页显示的数据条数
//定义全局变量
SQLHENV henv = NULL;//环境句柄
SQLHDBC hdbc = NULL;//连接句柄
SQLHSTMT hstmt = NULL;//语句句柄
SQLRETURN ret=NULL;//返回值

using namespace std;
//释放空间
void free()
{
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);//释放语句
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);//释放连接
    SQLFreeHandle(SQL_HANDLE_ENV, henv);//释放环境
}

//创建数据库
bool connect()//数据库连接函数
{
    SQLCHAR database[] = "dzy2";
    SQLCHAR username[] = "tobby";
    SQLCHAR password[] = "114514";
    SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//设置环境
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接
    ret = SQLConnect(hdbc, database, SQL_NTS, username, SQL_NTS, password, SQL_NTS);
    if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void insert(string name, bool gender, string major, string Class, string address, string birthdate) {
    connect();
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    string str1 = "use dzy2";
    string str2 = 
        "insert into student (name,gender,major,class,address,birthdate) values ('" + name + "'," + to_string(gender) + ",'" + major + "','" + Class + "','" + address + "','" + birthdate + "')";


    ret = SQLExecDirect(hstmt, (SQLCHAR*)str1.c_str(), SQL_NTS);
    ret = SQLExecDirect(hstmt, (SQLCHAR*)str2.c_str(), SQL_NTS);//execute
   if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "成功！" << endl;
    }
    else {
        cout << "失败！" << endl;
    }
   free();
}


void query(int page) {
    connect();
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    SQLCHAR sql1[] = "use dzy2";
    SQLCHAR sql2[] = "SELECT * FROM student ";
    ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
    ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
    query_print(page);
    free();
}
void query_print(int page) {
    //SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50], str6[50], str7[50];
    // SQLLEN name,number,gender,major,Class,address,birthdate;

    cout << setiosflags(ios::fixed) << setprecision(6) << setiosflags(ios::left);
    cout << setfill(' ') << "    " << setw(5) << "序号" << setw(14) << "姓名" << setw(6) << "学号" << setw(6) << "性别" << setw(19) << "专业" << setw(14) << "班级" << setw(14) << "籍贯" << setw(14) << "生日" << endl;
    int num = 1;
    if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
    {
        //查询之后，所有数据放到了一块缓冲区，我们需要把他分离出来

        int id = 0;
        TCHAR name[32] = { 0 };
        bool bgender = 0;
        string gender;
        TCHAR major[32] = { 0 };
        TCHAR Class[32] = { 0 };
        TCHAR address[32] = { 0 };
        TCHAR birthdate[32] = { 0 };
        //绑定字段
        SQLLEN len = SQL_NTS;
        SQLBindCol(hstmt, 1, SQL_C_CHAR, name, sizeof(name), &len);
        SQLBindCol(hstmt, 2, SQL_C_SHORT, &id, sizeof(id), 0);
        SQLBindCol(hstmt, 3, SQL_C_BIT, &bgender, sizeof(bgender), 0);
        SQLBindCol(hstmt, 4, SQL_C_CHAR, major, sizeof(major), &len);
        SQLBindCol(hstmt, 5, SQL_C_CHAR, Class, sizeof(Class), &len);
        SQLBindCol(hstmt, 6, SQL_C_CHAR, address, sizeof(address), &len);
        SQLBindCol(hstmt, 7, SQL_C_CHAR, birthdate, sizeof(birthdate), &len);

        //逐行遍历，获取数据
        ret = SQLFetch(hstmt);
        while (ret != SQL_NO_DATA && num <= page * DATAPERPAGE)
            //while (ret != SQL_NO_DATA)
        {
            if (bgender == 1) {
                gender = "男";
            }
            else {
                gender = "女";
            }
            if (num > (page - 1) * DATAPERPAGE) {
                cout << setfill(' ')<<"    "<<setw(5) << num << setw(14) << name << setw(6) << id << setw(6) << gender << setw(19) << major << setw(14) << Class << setw(14) << address << setw(14) << birthdate << endl;
            }
            num++;
            //每次清除一下上行的旧数据,保证下次获取的数据干净
            id = 0;
            ZeroMemory(name, sizeof(name));
            bgender = 0; gender = "";
            ZeroMemory(major, sizeof(major));
            ZeroMemory(Class, sizeof(Class));
            ZeroMemory(address, sizeof(address));
            ZeroMemory(birthdate, sizeof(birthdate));


            //获取下一行缓冲区的数据填充到id,name,age
            ret = SQLFetch(hstmt);
        }

        ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    }
    ret = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

}


bool search(searchBy mORc, string data,int page) {
    connect();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use dzy2";
	string sql2;
    if (mORc == MAJOR) {
		sql2 = "SELECT * FROM student where major='" + data + "'";
	}
    else if (mORc == CLASS) {
        sql2 = "SELECT * FROM student where class='" + data + "'";
	}
    else if (mORc == NAME) {
		sql2 = "SELECT * FROM student where name='" + data + "'";
	}
    else if (mORc == ID) {
		sql2 = "SELECT * FROM student where number='" + data + "'";
	}
	ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)sql2.c_str(), SQL_NTS);
	query_print(page);
	if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
		return true;
	else
		return false;
    free();
}

bool change(changeBy cha, string data, string id) {
    connect();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use dzy2";
	string sql2;
    if (cha == Ename) {
		sql2 = "update student set name='" + data + "' where number='" + id + "'";
	}
    else if (cha == Emajor) {
		sql2 = "update student set major='" + data + "' where number='" + id + "'";
	}
    else if (cha == EClass) {
		sql2 = "update student set class='" + data + "' where number='" + id + "'";
	}
    else if (cha == Eaddress) {
		sql2 = "update student set address='" + data + "' where number='" + id + "'";
	}
    else if (cha == Ebirthdate) {
		sql2 = "update student set birthdate='" + data + "' where number='" + id + "'";
	}
	ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)sql2.c_str(), SQL_NTS);
	if ((ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO))
		return true;
	else
		return false;
    free();
}

void getlast() {
    connect();
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use dzy2";
	SQLCHAR sql2[] = "SELECT TOP 1 * FROM student ORDER BY number DESC";
	ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
	ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
	query_print(1);
	free();
}
void delete_database() {
	connect();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use dzy2";
	SQLCHAR sql2[] = "delete from student";
	ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
	ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
	free();
}
void deleteStu(string id) {
	connect();
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	SQLCHAR sql1[] = "use dzy2";
	string sql2 = "delete from student where number='" + id + "'";
	ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)sql2.c_str(), SQL_NTS);
	free();
}