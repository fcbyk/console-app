#ifndef CONSOLE_APP_ADDRESSBOOK_H
#define CONSOLE_APP_ADDRESSBOOK_H
#endif

#include<iostream>
#include <string>
#include <limits>
#define MAX 1000 //最大人数

//联系人结构体
struct Person
{
    std::string m_Name; //姓名
    char m_Sex; //性别：1男 2女
    int m_Age; //年龄
    std::string m_Phone; //电话
    std::string m_Addr; //住址
};

//通讯录结构体
struct Addressbooks
{
    struct Person personArray[MAX]; //通讯录中保存的联系人数组
    int m_Size; //通讯录中人员个数
};

int AddressBookLaunch();
void showMenu();
void addPerson(Addressbooks *abs);
void showPerson(Addressbooks * abs);
int isExist(Addressbooks * abs, const std::string& name);
void deletePerson(Addressbooks * abs);
void findPerson(Addressbooks * abs);
void modifyPerson(Addressbooks * abs);
void cleanPerson(Addressbooks * abs);