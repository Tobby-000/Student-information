
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
			cout << "��¼�ɹ���" << endl;
            cout << "�����������ݿ�..." << endl;
            if (connect())
            {
                cout << "���ݿ����ӳɹ�!" << endl;
            }
            else
            {
                cout << "���ݿ�����ʧ�ܣ�" << endl;
                Sleep(10000);
                exit(0);
            }
            Sleep(1000);
            UI();
		}
        else
        {
			cout << "��¼ʧ�ܣ�" << endl;
			Sleep(5000);
			exit(0);
		}
    }
    else {
        exit(0);
    }
}
