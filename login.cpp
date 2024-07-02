#include"login.h"
#include<iostream>
#include<Windows.h>
#include<fstream>
#include<functional>
using namespace std;

bool login() {

	ifstream in("password.txt");
	if (!in) {
		cout << "文件打开失败！" << endl;
		cout<<"可能有文件缺失"<<endl;
		cout << "正在生成新文件" << endl;
		ofstream out("password.txt");
		if (!out) {
			cout << "文件生成失败！" << endl;
			return false;
		}

		out << -2073394602;
		cout << "文件生成成功！" << endl;
		cout << "默认密码为123456" << endl;
		cout<<"请尽快修改密码" << endl;
		cout<<"10秒后自动退出"<<endl;
		Sleep(10000);
		return false;
	}
	int password;
	hash<int> hash;
	cout << "请输入密码：";
	cin >> password;
	if (password == 0) {
		cout << "登录失败！" << endl;
		return 0;
	}
	int hash_password=hash._Do_hash(password);
	//cout << hash_password;
	password = 0;
	in >> password;
	if (password == hash_password) {
		return true;
	}
	else {

		Sleep(10000);
		exit(0);
		return false;
	}
}
bool change_password() {
	int password;
	cout << "请输入新密码：";
	cin >> password;
	hash<int> hash;
	int hash_password;
	hash_password = hash._Do_hash(password);
	fstream out("password.txt", ios::out | ios::trunc);
	if (!out)
	{
		cout << "文件打开失败！" << endl;
		return false;
	}
	out << hash_password;
	cout << "修改成功！" << endl;
	return true;
}