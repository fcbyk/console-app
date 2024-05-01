#ifndef CONSOLE_APP_WORKERMANAGER_H
#define CONSOLE_APP_WORKERMANAGER_H
#endif

#pragma once
#include<iostream>
#include <fstream>
#define  FILENAME "empFile.txt"


//职工抽象基类
class Worker{
public:
    int m_Id; //职工编号
    std::string m_Name; //职工姓名
    int m_DeptId; //职工所在部门名称编号

    virtual void showInfo() = 0;    //显示个人信息
    virtual std::string getDeptName() = 0;   //获取岗位名称
};

class WorkerManager
{
public:

    //构造函数
    WorkerManager();

    void WorkerManagerLaunch();

    void Show_Menu();

    void exitSystem();

    //记录文件中的人数个数
    int m_EmpNum;

    //员工数组的指针
    Worker ** m_EmpArray;

    //增加职工
    void Add_Emp();

    //保存文件
    void save();

    //标志文件是否为空
    bool m_FileIsEmpty;

    //统计人数
    int get_EmpNum();

    //初始化员工
    void init_Emp();

    //显示职工
    void Show_Emp();

    //删除职工
    void Del_Emp();

    //按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
    int IsExist(int id);

    //修改职工
    void Mod_Emp();

    //查找职工
    void Find_Emp();

    //排序职工
    void Sort_Emp();

    //清空文件
    void Clean_File();

    //析构函数
    ~WorkerManager();

};

