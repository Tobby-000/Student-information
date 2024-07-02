
#include<iostream>
#include<Windows.h>
#include<string>
#include <iomanip>
#include <conio.h> 
#include"login.h"
#include"database.h"
#include"ui.h"


using namespace std;



int main() {
    LoginUI();
    char ch = _getch();
    if (ch == '1') {
        if (login())
        {
			cout << "登录成功！" << endl;
            cout << "正在连接数据库..." << endl;
            if (connect())
            {
                cout << "数据库连接成功!" << endl;
            }
            else
            {
                cout << "数据库连接失败！" << endl;
                Sleep(10000);
                exit(0);
            }
            Sleep(1000);
            UI();
		}
        else
        {
			cout << "登录失败！" << endl;
			Sleep(5000);
			exit(0);
		}
    }
    else {
        exit(0);
    }
}
