#include"login.h"
#include<iostream>
#include<Windows.h>
#include<fstream>
#include<functional>
using namespace std;

bool login() {

	ifstream in("password.txt");
	if (!in) {
		cout << "�ļ���ʧ�ܣ�" << endl;
		cout<<"�������ļ�ȱʧ"<<endl;
		cout << "�����������ļ�" << endl;
		ofstream out("password.txt");
		if (!out) {
			cout << "�ļ�����ʧ�ܣ�" << endl;
			return false;
		}

		out << -2073394602;
		cout << "�ļ����ɳɹ���" << endl;
		cout << "Ĭ������Ϊ123456" << endl;
		cout<<"�뾡���޸�����" << endl;
		cout<<"10����Զ��˳�"<<endl;
		Sleep(10000);
		return false;
	}
	int password;
	hash<int> hash;
	cout << "���������룺";
	cin >> password;
	if (password == 0) {
		cout << "��¼ʧ�ܣ�" << endl;
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
	cout << "�����������룺";
	cin >> password;
	hash<int> hash;
	int hash_password;
	hash_password = hash._Do_hash(password);
	fstream out("password.txt", ios::out | ios::trunc);
	if (!out)
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return false;
	}
	out << hash_password;
	cout << "�޸ĳɹ���" << endl;
	return true;
}