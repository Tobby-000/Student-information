#include <iostream>  
#include <string>  
#include <conio.h> 
#include <Windows.h>
#include"ui.h"
#include"database.h"
#include"login.h"

using namespace std;
void LoginUI() {
	cout << "+-------------------------------------------------------------------------------------------------+" << endl;
	cout << "|                                     学生信息管理查询系统                                        |" << endl;
	cout << "+-------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                                 |" << endl;
    cout << "|                                                                                                 |" << endl;
    cout << "|                                                                                                 |" << endl;
	cout << "|                               1)登录               (输入密码以登录)                             |" << endl;
    cout << "|                                                                                                 |" << endl;
	cout << "|                               0)退出               (退出系统)                                   |" << endl;
    cout << "|                                                                                                 |" << endl;
    cout << "|                                                                                                 |" << endl;
    cout << "|                                                                                                 |" << endl;
	cout << "+-------------------------------------------------------------------------------------------------+" << endl;
	cout << "请输入选择" << endl;
}
void line() {
    cout << "+-------------------------------------------------------------------------------------------------+" << endl;
}
void UIdisplay() {
    // 清屏并重新绘制UI  
    system("cls"); // Windows特有命令，Linux下使用system("clear");  

    cout << "+-------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                    学生信息管理查询系统                                         |" << endl;
    cout << "+-------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                   1)修改登录密码        (管理员通过此功能修改密码)                              |" << endl;
    cout << "|                   2)学生信息查询        (可以根据姓名或学号来查找学生)                          |" << endl;
    cout << "|                   3)同专业学生查询      (可以查询到同专业的学生信息)                            |" << endl;
    cout << "|                   4)保存学生信息        (可输入学生信息并存入数据库)                            |" << endl;
    cout << "|                   5)读取录入的学生信息  (读取已录入的所有学生信息)                              |" << endl;
    cout << "|                   6)修改学生信息        (修改某一位学生的相关基本信息）                         |" << endl;
    cout << "|                   7)删除学生信息        (删除掉一条学生的记录)                                  |" << endl;
    cout << "|                   0)退出系统            (退出系统并退出登录）                                   |" << endl;
    cout << "|                   \')删库跑路            (真的是删库跑路，小心使用)                              |" << endl;
    cout << "+-------------------------------------------------------------------------------------------------+" << endl;

    // 提示用户输入  
    cout << "根据需要选择功能 0~7 " << endl;
}

int UI() {
    int cursorPos = 0;

    while (true) {
        UIdisplay();
        char ch = _getch(); // 读取用户输入但不显示  

        if (ch == '0') {
            return 0; // 退出循环  
        }

        if (ch == '1') {
            if (change_password()) {
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                cout << "|                                   修改成功，使用任意键回到主菜单                                |" << endl;
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                Sleep(1000);
                _getch();
                UIdisplay();
            }
            else {
				cout << "+-------------------------------------------------------------------------------------------------+" << endl;
				cout << "|                                    修改失败，使用任意键回到主菜单                               |" << endl;
				cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                Sleep(1000);
                _getch();
				UIdisplay();
            }
        }

        if (ch == '2') {
            cout << "要查询的学生信息或学号" << endl;
            cout<<"按1查询姓名，按2查询学号"<<endl;
            char ch2 = _getch();
            string str;
            if (ch2 == '1') {
				cout << "请输入要查询的姓名" << endl;
                cin>>str;
			}
            else if (ch2 == '2') {
                cout << "请输入要查询的学号" << endl;
                cin>>str;
            }
            else {
                cout << "输入错误" << endl;
				_getch();
				UIdisplay();
            }
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            if(ch2=='1')
            search(NAME, str, 1);
            if(ch2=='2')
            search(ID, str, 1);
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "|                                   查询完成，请按任意键回到主菜单                                |" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            _getch();
            UIdisplay();
        }
        if (ch == '3') {
            cout << "要查询的信息" << endl;
            cout<< "按1查询专业，按2查询班级" << endl;
            char ch2 = _getch();
            string str;
            if (ch2 == '1') {
                cout << "请输入要查询的专业" << endl;
                cin >> str;
            }
            else if (ch2 == '2') {
                cout << "请输入要查询的班级" << endl;
                cin >> str;
            }
            else {
                cout << "输入错误" << endl;
                _getch();
                UIdisplay();
            }
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            if (ch2 == '1')
                search(MAJOR, str, 1);
            if (ch2 == '2')
                search(CLASS, str, 1);
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "|                                    已完成，使用回车键回到主菜单                                 |" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            _getch();
            UIdisplay();
        }
        if (ch == '4') {
            cout << "请依次输入 姓名，性别，专业，班级，籍贯，生日(生日格式yyyy-mm-dd)" << endl;
            string name, gender,major, Class, address, birthdate;
            bool bgender;
            cin>> name >>gender>>major>>Class>>address>>birthdate;
            if(gender=="男")
                bgender = "1";
            else if(gender=="女")
                bgender = "0";
            else {
                cout<< "输入错误,任意键返回" << endl;
                _getch();
                UIdisplay();
            }
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            insert(name, bgender, major, Class, address, birthdate);
            getlast();
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "|                                   已保存，使用回车键回到主菜单                                  |" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            Sleep(1000);
            _getch();
            UIdisplay();
        }
        if (ch == '5') {
            int page = 1;
            system("cls");
            for (;;) {
				cout << "+-------------------------------------------------------------------------------------------------+" << endl;
				cout << "|                                      1)查看下一页                                               |" << endl;
				cout << "|                                      2)查看上一页                                               |" << endl;
				cout << "|                                      0)返回主菜单                                               |" << endl;
				cout << "+-------------------------------------------------------------------------------------------------+" << endl;

                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                query(page);
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                cout<<"PAGE:  "<< page << endl;
                Sleep(1000);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
                char ch2 = _getch();
                if (ch2 == '0') {
                    break;
                }
                else if (ch2 == '1') {
                    page++;
                    system("cls");
                }
                else if (ch2 == '2' && page > 1) {
                    page--;
                    system("cls");
                }
			}   
            Sleep(500);
            UIdisplay();
        }
        if (ch == '6') {
            for (;;) {
                cout << "请依次输入要修改的学生学号" << endl;
                string id;
                cin >> id;
                cout << "请输入要修改的信息" << endl;
                cout << "1)姓名 2)专业 3)班级 4)籍贯 5)生日" << endl;
                char ch2 = _getch();
                string data;
                if (ch2 == '1') {
                    cout << "请输入新的姓名" << endl;
                    cin >> data;
                    change(Ename, data, id);
                }
                else if (ch2 == '2') {
                    cout << "请输入新的专业" << endl;
                    cin >> data;
                    change(Emajor, data, id);
                }
                else if (ch2 == '3') {
                    cout << "请输入新的班级" << endl;
                    cin >> data;
                    change(EClass, data, id);
                }
                else if (ch2 == '4') {
                    cout << "请输入新的籍贯" << endl;
                    cin >> data;
                    change(Eaddress, data, id);
                }
                else if (ch2 == '5') {
                    cout << "请输入新的生日" << endl;
                    cin >> data;
                    change(Ebirthdate, data, id);
                }
                else {
                    cout << "输入错误" << endl;
                    Sleep(1000);
                    UIdisplay();
                    continue;
                }
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                search(ID, id, 1);
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                cout << "|                        已保存，输入0以继续修改，使用其他任意键回到主菜单                        |" << endl;
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                char ch3=_getch();
                UIdisplay();
                if (ch3 != '0') {
					break;
				}
            }
            
        }
        if (ch == '7') {
            cout << "请输入要删除的学生学号" << endl;
            string id;
            cin>> id;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            deleteStu(id);
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            cout << "|                                    已删除，使用任意键回到主菜单                                 |" << endl;
            cout << "+-------------------------------------------------------------------------------------------------+" << endl;
            _getch();
            UIdisplay();

        }
        if (ch == '\'') {
			cout << "你确定要删库跑路吗？" << endl;
			cout << "输入1确认，输入其他任意键取消" << endl;
			char ch2 = _getch();
            if (ch2 == '1') {
                cout<<"请输入登录密码，以确认删除数据库"<<endl;
                if (login()) {
                    cout << "正在删除数据库" << endl;
                    delete_database();
                    cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                    cout << "|                              数据库已删除，使用任意键回到主菜单                                 |" << endl;
                    cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                    _getch();
                    return 0;
                }
                else {
					cout << "+-------------------------------------------------------------------------------------------------+" << endl;
					cout << "|                                 密码错误，使用任意键回到主菜单                                  |" << endl;
					cout << "+-------------------------------------------------------------------------------------------------+" << endl;
					_getch();
					UIdisplay();
				}
			}
            else {
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
                cout << "|                                     删除已取消，使用任意键回到主菜单                            |" << endl;
                cout << "+-------------------------------------------------------------------------------------------------+" << endl;
				_getch();
				UIdisplay();
			}
		}
    }

    return 0;
}

