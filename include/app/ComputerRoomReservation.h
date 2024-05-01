#ifndef CONSOLE_APP_COMPUTERROOMRESERVATION_H
#define CONSOLE_APP_COMPUTERROOMRESERVATION_H
#endif
#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include<vector>
#include <algorithm>
#include <map>

//#define _CRT_SECURE_NO_WARNINGS

//管理员文件
#define ADMIN_FILE     "admin.txt"
//学生文件
#define STUDENT_FILE   "student.txt"
//教师文件
#define TEACHER_FILE   "teacher.txt"
//机房信息文件
#define COMPUTER_FILE  "computerRoom.txt"
//订单文件
#define ORDER_FILE     "order.txt"


//身份抽象类
class Identity
{
public:

    //操作菜单
    virtual void operMenu() = 0;

    std::string m_Name; //用户名
    std::string m_Pwd;  //密码
};


class OrderFile
{
public:

    //构造函数
    OrderFile();

    //更新预约记录
    void updateOrder();

    //记录的容器  key --- 记录的条数  value --- 具体记录的键值对信息
    std::map<int, std::map<std::string, std::string>> m_orderData;

    //预约记录条数
    int m_Size;
};


//机房类
class ComputerRoom
{
public:

    int m_ComId; //机房id号

    int m_MaxNum; //机房最大容量
};

//学生类
class Student :public Identity
{
public:
    //默认构造
    Student();

    //有参构造(学号、姓名、密码)
    Student(int id, std::string name, std::string pwd);

    //菜单界面
    virtual void operMenu();

    //申请预约
    void applyOrder();

    //查看我的预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生学号
    int m_Id;

    //机房容器
    std::vector<ComputerRoom> vCom;
};


class Teacher :public Identity{
public:
    int m_EmpId; //教师编号

    Teacher();  //默认构造
    //有参构造 (职工编号，姓名，密码)
    Teacher(int empId, std::string name, std::string pwd);
    virtual void operMenu(); //菜单界面
    void showAllOrder();    //查看所有预约
    void validOrder();      //审核预约
};

class ComputerManager :public Identity
{
public:

    //默认构造
    ComputerManager();

    //有参构造  管理员姓名，密码
    ComputerManager(std::string name, std::string pwd);

    //选择菜单
    virtual void operMenu();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //初始化容器
    void initVector();

    //学生容器
    std::vector<Student> vStu;

    //教师容器
    std::vector<Teacher> vTea;

    //检测重复 参数:(传入id，传入类型) 返回值：(true 代表有重复，false代表没有重复)
    bool checkRepeat(int id, int type);

    //机房容器
    std::vector<ComputerRoom> vCom;
};

class ComputerRoomReservation {
public:
    ComputerRoomReservation();

    int Launch();

    //教师菜单
    void TeacherMenu(Identity *teacher);

    //学生菜单
    void studentMenu(Identity * &student);

    //管理员菜单
    void managerMenu(Identity *manager);

    //登录功能
    void LoginIn(std::string fileName, int type);

};
