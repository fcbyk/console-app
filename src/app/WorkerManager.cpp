#include "./../../include/app/WorkerManager.h"

//mian方法启动
//WorkerManager wm;
//wm.WorkerManagerLaunch();
bool shouldExit = false; // 控制外部 while 循环的变量

class Boss :public Worker
{
public:

    Boss(int id, std::string name, int dId)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;

    }

    //显示个人信息
    void showInfo()
    {
        std::cout<< "职工编号： " << this->m_Id
                 << " \t职工姓名： " << this->m_Name
                 << " \t岗位：" << this->getDeptName()
                 << " \t岗位职责：管理公司所有事务" << std::endl;
    }

    //获取职工岗位名称
    std::string getDeptName()
    {
        return std::string("总裁");
    }
};

//员工类
class Employee :public Worker
{
public:

    //构造函数
    Employee(int id, std::string name, int dId)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;
    }


    //显示个人信息
    void showInfo()
    {
        std::cout<< "职工编号： " << this->m_Id
                 << " \t职工姓名： " << this->m_Name
                 << " \t岗位：" << this->getDeptName()
                 << " \t岗位职责：完成经理交给的任务" << std::endl;
    }

    //获取职工岗位名称
    std::string getDeptName()
    {
        return std::string("员工");
    }
};

//经理类
class Manager :public Worker
{
public:
    Manager(int id, std::string name, int dId)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_DeptId = dId;

    }

    //显示个人信息
    void showInfo()
    {
        std::cout<< "职工编号： " << this->m_Id
                 << " \t职工姓名： " << this->m_Name
                 << " \t岗位：" << this->getDeptName()
                 << " \t岗位职责：完成老板交给的任务,并下发任务给员工" << std::endl;
    }

    //获取职工岗位名称
    std::string getDeptName()
    {
        return std::string("经理");
    }
};

void WorkerManager::WorkerManagerLaunch() {
    int choice = 0;
    while (!shouldExit) {
        //展示菜单
        this->Show_Menu();
        std::cout<< "请输入您的选择:" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 0: //退出系统
                this->exitSystem();
                shouldExit = true; // 终止外部循环
                getchar();
                break;
            case 1: //添加职工
                this->Add_Emp();
                break;
            case 2: //显示职工
                this->Show_Emp();
                break;
            case 3: //删除职工
                this->Del_Emp();
                break;
            case 4: //修改职工
                this->Mod_Emp();
                break;
            case 5: //查找职工
                this->Find_Emp();
                break;
            case 6: //排序职工
                this->Sort_Emp();
                break;
            case 7: //清空文件
                this->Clean_File();
                break;
            default:
                system("cls");
                break;
        }
    }
}

WorkerManager::WorkerManager() {
    std::ifstream ifs;
    ifs.open(FILENAME, std::ios::in);

    //文件不存在情况
    if (!ifs.is_open()) {
//        std::cout<< "文件不存在" << std::endl; //测试输出
        this->m_EmpNum = 0;  //初始化人数
        this->m_FileIsEmpty = true; //初始化文件为空标志
        this->m_EmpArray = NULL; //初始化数组
        ifs.close(); //关闭文件
        return;
    }

    //文件存在，并且没有记录
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
//        std::cout<< "文件为空!" << std::endl;
        this->m_EmpNum = 0;
        this->m_FileIsEmpty = true;
        this->m_EmpArray = NULL;
        ifs.close();
        return;
    }

    int num = this->get_EmpNum();
    this->m_EmpNum = num;  //更新成员属性

    //根据职工数创建数组
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    //初始化职工
    init_Emp();

}

void WorkerManager::Show_Menu() {
    std::cout<< " ------------------------------------------" << std::endl;
    std::cout<< "|            欢迎使用职工管理系统！        |" << std::endl;
    std::cout<< "|              0.退出管理程序              |" << std::endl;
    std::cout<< "|              1.增加职工信息              |" << std::endl;
    std::cout<< "|              2.显示职工信息              |" << std::endl;
    std::cout<< "|              3.删除离职职工              |" << std::endl;
    std::cout<< "|              4.修改职工信息              |" << std::endl;
    std::cout<< "|              5.查找职工信息              |" << std::endl;
    std::cout<< "|              6.按照编号排序              |" << std::endl;
    std::cout<< "|              7.清空所有文档              |" << std::endl;
    std::cout<< " ------------------------------------------" << std::endl;
    std::cout<< std::endl;
}

void WorkerManager::exitSystem() {
    std::cout<< "欢迎下次使用" << std::endl;
    system("pause");
//    exit(0);
}

//增加职工
void WorkerManager::Add_Emp() {
    std::cout<< "请输入增加职工数量： " << std::endl;

    int addNum = 0;
    std::cin >> addNum;

    if (addNum > 0) {
        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        Worker **newSpace = new Worker *[newSize];

        //将原空间下内容存放到新空间下
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //输入新数据
        for (int i = 0; i < addNum; i++) {
            int id;
            std::string name;
            int dSelect;

            std::cout<< "请输入第 " << i + 1 << " 个新职工编号：" << std::endl;
            std::cin >> id;


            std::cout<< "请输入第 " << i + 1 << " 个新职工姓名：" << std::endl;
            std::cin >> name;


            std::cout<< "请选择该职工的岗位：" << std::endl;
            std::cout<< "1、普通职工" << std::endl;
            std::cout<< "2、经理" << std::endl;
            std::cout<< "3、老板" << std::endl;
            std::cin >> dSelect;


            Worker *worker = NULL;
            switch (dSelect) {
                case 1: //普通员工
                    worker = new Employee(id, name, 1);
                    break;
                case 2: //经理
                    worker = new Manager(id, name, 2);
                    break;
                case 3:  //老板
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
            }


            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原有空间
        delete[] this->m_EmpArray;

        //更改新空间的指向
        this->m_EmpArray = newSpace;

        //更新新的个数
        this->m_EmpNum = newSize;

        //更新职工不为空标志
        this->m_FileIsEmpty = false;

        //提示信息
        std::cout<< "成功添加" << addNum << "名新职工！" << std::endl;

        //保存到文件中
        this->save();
    } else {
        std::cout<< "输入有误" << std::endl;
    }

    system("pause");
    system("cls");
}

void WorkerManager::save() {
    std::ofstream ofs;
    ofs.open(FILENAME, std::ios::out);


    for (int i = 0; i < this->m_EmpNum; i++) {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << std::endl;
    }

    ofs.close();
}

int WorkerManager::get_EmpNum() {
    std::ifstream ifs;
    ifs.open(FILENAME, std::ios::in);

    int id;
    std::string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId) {
        //记录人数
        num++;
    }
    ifs.close();

    return num;
}

void WorkerManager::init_Emp() {
    std::ifstream ifs;
    ifs.open(FILENAME, std::ios::in);

    int id;
    std::string name;
    int dId;

    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId) {
        Worker *worker = NULL;
        //根据不同的部门Id创建不同对象
        if (dId == 1)  // 1普通员工
        {
            worker = new Employee(id, name, dId);
        } else if (dId == 2) //2经理
        {
            worker = new Manager(id, name, dId);
        } else //总裁
        {
            worker = new Boss(id, name, dId);
        }
        //存放在数组中
        this->m_EmpArray[index] = worker;
        index++;
    }
}

//显示职工
void WorkerManager::Show_Emp() {
    if (this->m_FileIsEmpty) {
        std::cout<< "文件不存在或记录为空！" << std::endl;
    } else {
        for (int i = 0; i < m_EmpNum; i++) {
            //利用多态调用接口
            this->m_EmpArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");
}

int WorkerManager::IsExist(int id) {
    int index = -1;

    for (int i = 0; i < this->m_EmpNum; i++) {
        if (this->m_EmpArray[i]->m_Id == id) {
            index = i;

            break;
        }
    }

    return index;
}

//删除职工
void WorkerManager::Del_Emp() {
    if (this->m_FileIsEmpty) {
        std::cout<< "文件不存在或记录为空！" << std::endl;
    } else {
        //按职工编号删除
        std::cout<< "请输入想要删除的职工号：" << std::endl;
        int id = 0;
        std::cin >> id;

        int index = this->IsExist(id);

        if (index != -1)  //说明index上位置数据需要删除
        {
            for (int i = index; i < this->m_EmpNum - 1; i++) {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;

            this->save(); //删除后数据同步到文件中
            std::cout<< "删除成功！" << std::endl;
        } else {
            std::cout<< "删除失败，未找到该职工" << std::endl;
        }
    }

    system("pause");
    system("cls");
}

//修改职工
void WorkerManager::Mod_Emp() {
    if (this->m_FileIsEmpty) {
        std::cout<< "文件不存在或记录为空！" << std::endl;
    } else {
        std::cout<< "请输入修改职工的编号：" << std::endl;
        int id;
        std::cin >> id;

        int ret = this->IsExist(id);
        if (ret != -1) {
            //查找到编号的职工

            delete this->m_EmpArray[ret];

            int newId = 0;
            std::string newName = "";
            int dSelect = 0;

            std::cout<< "查到： " << id << "号职工，请输入新职工号： " << std::endl;
            std::cin >> newId;

            std::cout<< "请输入新姓名： " << std::endl;
            std::cin >> newName;

            std::cout<< "请输入岗位： " << std::endl;
            std::cout<< "1、普通职工" << std::endl;
            std::cout<< "2、经理" << std::endl;
            std::cout<< "3、老板" << std::endl;
            std::cin >> dSelect;

            Worker *worker = NULL;
            switch (dSelect) {
                case 1:
                    worker = new Employee(newId, newName, dSelect);
                    break;
                case 2:
                    worker = new Manager(newId, newName, dSelect);
                    break;
                case 3:
                    worker = new Boss(newId, newName, dSelect);
                    break;
                default:
                    break;
            }

            //更改数据 到数组中
            this->m_EmpArray[ret] = worker;

            std::cout<< "修改成功！" << std::endl;

            //保存到文件中
            this->save();
        } else {
            std::cout<< "修改失败，查无此人" << std::endl;
        }
    }

    //按任意键 清屏
    system("pause");
    system("cls");
}

//查找职工
void WorkerManager::Find_Emp() {
    if (this->m_FileIsEmpty) {
        std::cout<< "文件不存在或记录为空！" << std::endl;
    } else {
        std::cout<< "请输入查找的方式：" << std::endl;
        std::cout<< "1、按职工编号查找" << std::endl;
        std::cout<< "2、按姓名查找" << std::endl;

        int select = 0;
        std::cin >> select;


        if (select == 1) //按职工号查找
        {
            int id;
            std::cout<< "请输入查找的职工编号：" << std::endl;
            std::cin >> id;

            int ret = IsExist(id);
            if (ret != -1) {
                std::cout<< "查找成功！该职工信息如下：" << std::endl;
                this->m_EmpArray[ret]->showInfo();
            } else {
                std::cout<< "查找失败，查无此人" << std::endl;
            }
        } else if (select == 2) //按姓名查找
        {
            std::string name;
            std::cout<< "请输入查找的姓名：" << std::endl;
            std::cin >> name;

            bool flag = false;  //查找到的标志
            for (int i = 0; i < m_EmpNum; i++) {
                if (m_EmpArray[i]->m_Name == name) {
                    std::cout<< "查找成功,职工编号为："
                         << m_EmpArray[i]->m_Id
                         << " 号的信息如下：" << std::endl;

                    flag = true;

                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false) {
                //查无此人
                std::cout<< "查找失败，查无此人" << std::endl;
            }
        } else {
            std::cout<< "输入选项有误" << std::endl;
        }
    }


    system("pause");
    system("cls");
}

//排序职工
void WorkerManager::Sort_Emp() {
    if (this->m_FileIsEmpty) {
        std::cout<< "文件不存在或记录为空！" << std::endl;
        system("pause");
        system("cls");
    } else {
        std::cout<< "请选择排序方式： " << std::endl;
        std::cout<< "1、按职工号进行升序" << std::endl;
        std::cout<< "2、按职工号进行降序" << std::endl;

        int select = 0;
        std::cin >> select;


        for (int i = 0; i < m_EmpNum; i++) {
            int minOrMax = i;
            for (int j = i + 1; j < m_EmpNum; j++) {
                if (select == 1) //升序
                {
                    if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
                        minOrMax = j;
                    }
                } else  //降序
                {
                    if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
                        minOrMax = j;
                    }
                }
            }

            if (i != minOrMax) {
                Worker *temp = m_EmpArray[i];
                m_EmpArray[i] = m_EmpArray[minOrMax];
                m_EmpArray[minOrMax] = temp;
            }

        }

        std::cout<< "排序成功,排序后结果为：" << std::endl;
        this->save();
        this->Show_Emp();
    }

}

//清空文件
void WorkerManager::Clean_File() {
    std::cout<< "确认清空？" << std::endl;
    std::cout<< "1、确认" << std::endl;
    std::cout<< "2、返回" << std::endl;

    int select = 0;
    std::cin >> select;

    if (select == 1) {
        //打开模式 std::ios::trunc 如果存在删除文件并重新创建
        std::ofstream ofs(FILENAME, std::ios::trunc);
        ofs.close();

        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray[i] != NULL) {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_FileIsEmpty = true;
        }
        std::cout<< "清空成功！" << std::endl;
    }

    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager() {
    if (this->m_EmpArray != NULL) {
        delete[] this->m_EmpArray;
    }
}