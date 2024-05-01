#include "./../../include/app/ComputerRoomReservation.h"

int ComputerRoomReservation::Launch(){
    int select = 0;

    while (true)
    {

        std::cout << "======================  欢迎来到传智播客机房预约系统  =====================" << std::endl;
        std::cout << std::endl << "请输入您的身份" << std::endl;
        std::cout << "\t\t -------------------------------\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|          1.学生代表           |\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|          2.老    师           |\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|          3.管 理 员           |\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|          0.退    出           |\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t -------------------------------\n";
        std::cout << "输入您的选择: ";

        std::cin >> select; //接受用户选择

        switch (select)
        {
            case 1:  //学生身份
                LoginIn(STUDENT_FILE,1);
                break;
            case 2:  //老师身份
                LoginIn(TEACHER_FILE,2);
                break;
            case 3:  //管理员身份
                LoginIn(ADMIN_FILE,3);
                break;
            case 0:  //退出系统
                std::cout << "欢迎下一次使用" << std::endl;
                system("pause");
                getchar();
                return 0;
                break;
            default:
                std::cout << "输入有误，请重新选择！" << std::endl;
                system("pause");
                system("cls");
                break;
        }

    }
}

ComputerRoomReservation::ComputerRoomReservation() {

}

//教师菜单
void ComputerRoomReservation::TeacherMenu(Identity *teacher)
{
    while (true)
    {
        //教师菜单
        teacher->operMenu();

        Teacher* tea = (Teacher*)teacher;
        int select = 0;

        std::cin >> select;

        if (select == 1)
        {
            //查看所有预约
            tea->showAllOrder();
        }
        else if (select == 2)
        {
            //审核预约
            tea->validOrder();
        }
        else
        {
            delete teacher;
            std::cout << "注销成功" << std::endl;
            system("pause");
            system("cls");
            return;
        }

    }
}

//学生菜单
void ComputerRoomReservation::studentMenu(Identity * &student)
{
    while (true)
    {
        //学生菜单
        student->operMenu();

        Student* stu = (Student*)student;
        int select = 0;

        std::cin >> select;

        if (select == 1) //申请预约
        {
            stu->applyOrder();
        }
        else if (select == 2) //查看自身预约
        {
            stu->showMyOrder();
        }
        else if (select == 3) //查看所有预约
        {
            stu->showAllOrder();
        }
        else if (select == 4) //取消预约
        {
            stu->cancelOrder();
        }
        else
        {
            delete student;
            std::cout << "注销成功" << std::endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//管理员菜单
void ComputerRoomReservation::managerMenu(Identity *manager)
{
    while (true)
    {
        //管理员菜单
        manager->operMenu();

        ComputerManager* man = (ComputerManager*)manager;
        int select = 0;

        std::cin >> select;

        if (select == 1)  //添加账号
        {
            std::cout << "添加账号" << std::endl;
            man->addPerson();
        }
        else if (select == 2) //查看账号
        {
            std::cout << "查看账号" << std::endl;
            man->showPerson();
        }
        else if (select == 3) //查看机房
        {
            std::cout << "查看机房" << std::endl;
            man->showComputer();
        }
        else if (select == 4) //清空预约
        {
            std::cout << "清空预约" << std::endl;
            man->cleanFile();
        }
        else
        {
            delete manager;
            std::cout << "注销成功" << std::endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//登录功能
void ComputerRoomReservation::LoginIn(std::string fileName, int type)
{

    Identity *person = NULL;

    std::ifstream ifs;
    ifs.open(fileName, std::ios::in);

    //文件不存在情况
    if (!ifs.is_open())
    {
        std::cout << "文件不存在" << std::endl;
        ifs.close();
        system("pause");
        system("cls");
        return;
    }

    int id = 0;
    std::string name;
    std::string pwd;

    if (type == 1)	//学生登录
    {
        std::cout << "请输入你的学号" << std::endl;
        std::cin >> id;
    }
    else if (type == 2) //教师登录
    {
        std::cout << "请输入你的职工号" << std::endl;
        std::cin >> id;
    }

    std::cout << "请输入用户名：" << std::endl;
    std::cin >> name;

    std::cout << "请输入密码： " << std::endl;
    std::cin >> pwd;


    if (type == 1)
    {
        //学生登录验证
        int fId;
        std::string fName;
        std::string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (id == fId && name == fName && pwd == fPwd)
            {
                std::cout << "学生验证登录成功!" << std::endl;
                system("pause");
                system("cls");
                person = new Student(id, name, pwd);
                //进入学生子菜单
                studentMenu(person);
                return;
            }
        }
    }
    else if (type == 2)
    {
        //教师登录验证
        int fId;
        std::string fName;
        std::string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (id == fId && name == fName && pwd == fPwd)
            {
                std::cout << "教师验证登录成功!" << std::endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, pwd);
                //进入教师子菜单
                TeacherMenu(person);
                return;
            }
        }
    }
    else if(type == 3)
    {
        //管理员登录验证
        std::string fName;
        std::string fPwd;
        while (ifs >> fName && ifs >> fPwd)
        {
            if (name == fName && pwd == fPwd)
            {
                std::cout << "验证登录成功!" << std::endl;
                //登录成功后，按任意键进入管理员界面
                system("pause");
                system("cls");
                //创建管理员对象
                person = new ComputerManager(name,pwd);
                //进入管理员子菜单
                managerMenu(person);
                return;
            }
        }
    }

    std::cout << "验证登录失败!" << std::endl;

    system("pause");
    system("cls");
    return;
}

class Circle{
public:
    int r;

    double CircleArea(){
        return 3.14 * r * r;
    }

    double CircleZC(){
        return 2 * 3.14 * r;
    }
};

//默认构造
ComputerManager::ComputerManager()
{
}

//有参构造
ComputerManager::ComputerManager(std::string name, std::string pwd)
{
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器
    this->initVector();

    //获取机房信息
    std::ifstream ifs;

    ifs.open(COMPUTER_FILE, std::ios::in);

    ComputerRoom c;
    while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
    {
        vCom.push_back(c);
    }
    std::cout << "当前机房数量为： " << vCom.size() << std::endl;

    ifs.close();
}

//选择菜单
void ComputerManager::operMenu()
{
    std::cout << "欢迎管理员："<<this->m_Name << "登录！" << std::endl;
    std::cout << "\t\t ---------------------------------\n";
    std::cout << "\t\t|                                |\n";
    std::cout << "\t\t|          1.添加账号            |\n";
    std::cout << "\t\t|                                |\n";
    std::cout << "\t\t|          2.查看账号            |\n";
    std::cout << "\t\t|                                |\n";
    std::cout << "\t\t|          3.查看机房            |\n";
    std::cout << "\t\t|                                |\n";
    std::cout << "\t\t|          4.清空预约            |\n";
    std::cout << "\t\t|                                |\n";
    std::cout << "\t\t|          0.注销登录            |\n";
    std::cout << "\t\t|                                |\n";
    std::cout << "\t\t ---------------------------------\n";
    std::cout << "请选择您的操作： " << std::endl;
}

//添加账号
void ComputerManager::addPerson()
{

    std::cout << "请输入添加账号的类型" << std::endl;
    std::cout << "1、添加学生" << std::endl;
    std::cout << "2、添加老师" << std::endl;

    std::string fileName;
    std::string tip;
    std::ofstream ofs;

    int select = 0;
    std::cin >> select;

    std::string errorTip; //重复错误提示

    if (select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "请输入学号： ";
        errorTip = "学号重复，请重新输入";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工编号：";
        errorTip = "职工号重复，请重新输入";
    }
    ofs.open(fileName, std::ios::out | std::ios::app);
    int id;
    std::string name;
    std::string pwd;
    std::cout <<tip << std::endl;

    while (true)
    {
        std::cin >> id;

        bool ret = this->checkRepeat(id, 1);

        if (ret) //有重复
        {
            std::cout << errorTip << std::endl;
        }
        else
        {
            break;
        }
    }

    std::cout << "请输入姓名： " << std::endl;
    std::cin >> name;

    std::cout << "请输入密码： " << std::endl;
    std::cin >> pwd;

    ofs << id << " " << name << " " << pwd << " " << std::endl;
    std::cout << "添加成功" << std::endl;

    system("pause");
    system("cls");

    ofs.close();

    //初始化容器
    this->initVector();
}

void printStudent(Student & s)
{
    std::cout << "学号： " << s.m_Id << " 姓名： " << s.m_Name << " 密码：" << s.m_Pwd << std::endl;
}
void printTeacher(Teacher & t)
{
    std::cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_Name << " 密码：" << t.m_Pwd << std::endl;
}

void ComputerManager::showPerson()
{
    std::cout << "请选择查看内容：" << std::endl;
    std::cout << "1、查看所有学生" << std::endl;
    std::cout << "2、查看所有老师" << std::endl;

    int select = 0;

    std::cin >> select;

    if (select == 1)
    {
        std::cout << "所有学生信息如下： " << std::endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    }
    else
    {
        std::cout << "所有老师信息如下： " << std::endl;
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }
    system("pause");
    system("cls");
}

//查看机房信息
void ComputerManager::showComputer()
{
    std::cout << "机房信息如下： " << std::endl;
    for (std::vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        std::cout << "机房编号： " << it->m_ComId << " 机房最大容量： " << it->m_MaxNum << std::endl;
    }
    system("pause");
    system("cls");
}

//清空预约记录
void ComputerManager::cleanFile()
{
    std::ofstream ofs(ORDER_FILE, std::ios::trunc);
    ofs.close();

    std::cout << "清空成功！" << std::endl;
    system("pause");
    system("cls");
}

void ComputerManager::initVector()
{
    //读取学生文件中信息
    std::ifstream ifs;
    ifs.open(STUDENT_FILE, std::ios::in);
    if (!ifs.is_open())
    {
        std::cout << "文件读取失败" << std::endl;
        return;
    }

    vStu.clear();
    vTea.clear();

    Student s;
    while (ifs >> s.m_Id && ifs >> s.m_Name &&  ifs >> s.m_Pwd)
    {
        vStu.push_back(s);
    }
    std::cout << "当前学生数量为： " << vStu.size() << std::endl;
    ifs.close(); //学生初始化

    //读取老师文件信息
    ifs.open(TEACHER_FILE, std::ios::in);

    Teacher t;
    while (ifs >> t.m_EmpId && ifs >> t.m_Name &&  ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    std::cout << "当前教师数量为： " << vTea.size() << std::endl;

    ifs.close();
}

bool ComputerManager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        for (std::vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            if (id == it->m_Id)
            {
                return true;
            }
        }
    }
    else
    {
        for (std::vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if (id == it->m_EmpId)
            {
                return true;
            }
        }
    }
    return false;
}

OrderFile::OrderFile()
{
    std::ifstream ifs;
    ifs.open(ORDER_FILE, std::ios::in);

    std::string date;      //日期
    std::string interval;  //时间段
    std::string stuId;     //学生编号
    std::string stuName;   //学生姓名
    std::string roomId;    //机房编号
    std::string status;    //预约状态


    this->m_Size = 0; //预约记录个数

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId &&  ifs >> status)
    {
        //测试代码
        /*
        std::cout << date << std::endl;
        std::cout << interval << std::endl;
        std::cout << stuId << std::endl;
        std::cout << stuName << std::endl;
        std::cout << roomId << std::endl;
        std::cout << status << std::endl;
        */

        std::string key;
        std::string value;
        std::map<std::string, std::string> m;

        int pos = date.find(":");
        if (pos != -1)
        {
            key = date.substr(0, pos);
            value = date.substr(pos + 1, date.size() - pos -1);
            m.insert(make_pair(key, value));
        }

        pos = interval.find(":");
        if (pos != -1)
        {
            key = interval.substr(0, pos);
            value = interval.substr(pos + 1, interval.size() - pos -1 );
            m.insert(make_pair(key, value));
        }

        pos = stuId.find(":");
        if (pos != -1)
        {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos + 1, stuId.size() - pos -1 );
            m.insert(make_pair(key, value));
        }

        pos = stuName.find(":");
        if (pos != -1)
        {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos + 1, stuName.size() - pos -1);
            m.insert(make_pair(key, value));
        }

        pos = roomId.find(":");
        if (pos != -1)
        {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos + 1, roomId.size() - pos -1 );
            m.insert(make_pair(key, value));
        }

        pos = status.find(":");
        if (pos != -1)
        {
            key = status.substr(0, pos);
            value = status.substr(pos + 1, status.size() - pos -1);
            m.insert(make_pair(key, value));
        }


        this->m_orderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }

    //测试代码
    //for (map<int, map<std::string, std::string>>::iterator it = m_orderData.begin(); it != m_orderData.end();it++)
    //{
    //	std::cout << "key = " << it->first << " value = " << std::endl;
    //	for (map<std::string, std::string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
    //	{
    //		std::cout << mit->first << " " << mit->second << " ";
    //	}
    //	std::cout << std::endl;
    //}

    ifs.close();
}

void OrderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return;
    }

    std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::trunc);
    for (int i = 0; i < m_Size;i++)
    {
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << std::endl;
    }
    ofs.close();
}


//默认构造
Student::Student()
{
}

//有参构造(学号、姓名、密码)
Student::Student(int id, std::string name, std::string pwd)
{
    //初始化属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    //获取机房信息
    std::ifstream ifs;
    ifs.open(COMPUTER_FILE, std::ios::in);

    ComputerRoom c;
    while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
    {
        vCom.push_back(c);
    }

    ifs.close();
}

//菜单界面
void Student::operMenu()
{
    std::cout << "欢迎学生代表：" << this->m_Name << "登录！" << std::endl;
    std::cout << "\t\t ----------------------------------\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          1.申请预约              |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          2.查看我的预约          |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          3.查看所有预约          |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          4.取消预约              |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          0.注销登录              |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t ----------------------------------\n";
    std::cout << "请选择您的操作： " << std::endl;
}

//申请预约
void Student::applyOrder()
{
    std::cout << "机房开放时间为周一至周五！" << std::endl;
    std::cout << "请输入申请预约的时间：" << std::endl;
    std::cout << "1、周一" << std::endl;
    std::cout << "2、周二" << std::endl;
    std::cout << "3、周三" << std::endl;
    std::cout << "4、周四" << std::endl;
    std::cout << "5、周五" << std::endl;
    int date = 0;
    int interval = 0;
    int room = 0;

    while (true)
    {
        std::cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }


    std::cout << "请输入申请预约的时间段：" << std::endl;
    std::cout << "1、上午" << std::endl;
    std::cout << "2、下午" << std::endl;

    while (true)
    {
        std::cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    std::cout << "请选择机房：" << std::endl;
    std::cout << "1号机房容量：" << vCom[0].m_MaxNum << std::endl;
    std::cout << "2号机房容量：" << vCom[1].m_MaxNum << std::endl;
    std::cout << "3号机房容量：" << vCom[2].m_MaxNum << std::endl;

    while (true)
    {
        std::cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    std::cout << "预约成功！审核中" << std::endl;

    std::ofstream ofs(ORDER_FILE, std::ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << std::endl;

    ofs.close();

    system("pause");
    system("cls");
}

//查看我的预约
void Student::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        std::cout << "无预约记录" << std::endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
            std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            std::cout << " 机房：" << of.m_orderData[i]["roomId"];
            std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if (of.m_orderData[i]["status"] == "-1")
            {
                status += "审核未通过，预约失败";
            }
            else
            {
                status += "预约已取消";
            }
            std::cout << status << std::endl;

        }
    }

    system("pause");
    system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        std::cout << "无预约记录" << std::endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < of.m_Size; i++)
    {
        std::cout << i + 1 << "、 ";

        std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
        std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        std::cout << " 学号：" << of.m_orderData[i]["stuId"];
        std::cout << " 姓名：" << of.m_orderData[i]["stuName"];
        std::cout << " 机房：" << of.m_orderData[i]["roomId"];
        std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "审核未通过，预约失败";
        }
        else
        {
            status += "预约已取消";
        }
        std::cout << status << std::endl;
    }

    system("pause");
    system("cls");
}

//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        std::cout << "无预约记录" << std::endl;
        system("pause");
        system("cls");
        return;
    }
    std::cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << std::endl;

    std::vector<int>v;
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                std::cout <<  index ++  << "、 ";
                std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
                std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
                std::cout << " 机房：" << of.m_orderData[i]["roomId"];
                std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                else if (of.m_orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                std::cout << status << std::endl;

            }
        }
    }

    std::cout << "请输入取消的记录,0代表返回" << std::endl;
    int select = 0;
    while (true)
    {
        std::cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                //	std::cout << "记录所在位置： " << v[select - 1] << std::endl;
                of.m_orderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                std::cout << "已取消预约" << std::endl;
                break;
            }

        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    system("pause");
    system("cls");
}

//默认构造
Teacher::Teacher()
{
}

//有参构造 (职工编号，姓名，密码)
Teacher::Teacher(int empId, std::string name, std::string pwd)
{
    //初始化属性
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//教师菜单界面
void Teacher::operMenu()
{
    std::cout << "欢迎教师：" << this->m_Name << "登录！" << std::endl;
    std::cout << "\t\t ----------------------------------\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          1.查看所有预约          |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          2.审核预约              |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t|          0.注销登录              |\n";
    std::cout << "\t\t|                                  |\n";
    std::cout << "\t\t ----------------------------------\n";
    std::cout << "请选择您的操作： " << std::endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        std::cout << "无预约记录" << std::endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
        std::cout << i + 1 << "、 ";

        std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
        std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        std::cout << " 学号：" << of.m_orderData[i]["stuId"];
        std::cout << " 姓名：" << of.m_orderData[i]["stuName"];
        std::cout << " 机房：" << of.m_orderData[i]["roomId"];
        std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "审核未通过，预约失败";
        }
        else
        {
            status += "预约已取消";
        }
        std::cout << status << std::endl;
    }

    system("pause");
    system("cls");
}

//审核预约
void Teacher::validOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        std::cout << "无预约记录" << std::endl;
        system("pause");
        system("cls");
        return;
    }
    std::cout << "待审核的预约记录如下：" << std::endl;

    std::vector<int>v;
    int index = 0;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            std::cout << ++index << "、 ";
            std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
            std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            std::cout << " 机房：" << of.m_orderData[i]["roomId"];
            std::string status = " 状态： ";  // 0取消的预约   1 审核中   2 已预约  -1 预约失败
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            std::cout << status << std::endl;
        }
    }
    std::cout << "请输入审核的预约记录,0代表返回" << std::endl;
    int select = 0;
    int ret = 0;
    while (true)
    {
        std::cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                std::cout << "请输入审核结果" << std::endl;
                std::cout << "1、通过" << std::endl;
                std::cout << "2、不通过" << std::endl;
                std::cin >> ret;

                if (ret == 1)
                {
                    of.m_orderData[v[select - 1]]["status"] = "2";
                }
                else
                {
                    of.m_orderData[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();
                std::cout << "审核完毕！" << std::endl;
                break;
            }
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    system("pause");
    system("cls");
}