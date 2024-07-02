#pragma once

#include <iostream>
using namespace std;

enum searchBy {
    NAME,
    ID,
    MAJOR,
    CLASS,
};

enum changeBy {
    Ename,
    Emajor,
    EClass,
    Eaddress,
    Ebirthdate,

};


void free();
bool connect();
void insert(string name, bool gender, string major, string Class, string address, string birthdate);
void getlast();
void query(int page);
void query_print(int page);
void deleteStu(string id);
void delete_database();
bool search(searchBy sear, string majorORclass,int page);
bool change(changeBy cha, string data, string id);
