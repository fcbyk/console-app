#include "./../../include/app/addressBook.h"

//启动程序
int AddressBookLaunch(){
    //创建通讯录
    Addressbooks abs;
    //初始化通讯录中人数
    abs.m_Size = 0;

    std::string select;

    while (true) {
        system("cls");
        showMenu();

        getline(std::cin,select);

        switch (select[0]) {
            case '1':  //添加联系人
                addPerson(&abs);
                break;
            case '2':  //显示联系人
                showPerson(&abs);
                break;
            case '3':  //删除联系人
                deletePerson(&abs);
                break;
            case '4':  //查找联系人
                findPerson(&abs);
                break;
            case '5':  //修改联系人
                modifyPerson(&abs);
                break;
            case '6':  //清空联系人
                cleanPerson(&abs);
                break;
            case '0':  //退出通讯录
                std::cout << "欢迎下次使用" << std::endl;
                system("pause");
                return 0;
            default:
                std::cout << "输入有误" << std::endl;
                system("pause");
                break;
        }
    }
}

//菜单界面
void showMenu()
{
    std::cout << "------------------" << std::endl;
    std::cout << "|  1、添加联系人  |" << std::endl;
    std::cout << "|  2、显示联系人  |" << std::endl;
    std::cout << "|  3、删除联系人  |" << std::endl;
    std::cout << "|  4、查找联系人  |" << std::endl;
    std::cout << "|  5、修改联系人  |" << std::endl;
    std::cout << "|  6、清空联系人  |" << std::endl;
    std::cout << "|  0、退出通讯录  |" << std::endl;
    std::cout << "------------------" << std::endl;
}

//1、添加联系人信息
void addPerson(Addressbooks *abs)
{
    //判断电话本是否满了
    if (abs->m_Size == MAX)
    {
        std::cout << "通讯录已满，无法添加" << std::endl;
        return;
    }
    else
    {
        //姓名
        std::string name;
        std::cout << "请输入姓名：" << std::endl;
        std::cin >> name;
        abs->personArray[abs->m_Size].m_Name = name;

        std::cout << "请输入性别：" << std::endl;
        std::cout << "1男，2女" << std::endl;

        //性别
        std::string sex = "0";
        while (true)
        {
            std::cin >> sex;
            if (sex[0] == '1' || sex[0] == '2')
            {
                abs->personArray[abs->m_Size].m_Sex = sex[0];
                break;
            }
            std::cout << "输入有误，请重新输入";
        }

        //年龄
//            std::cout << "请输入年龄：" << std::endl;
//            int age = 0;
//            std::cin >> age;
//            abs->personArray[abs->m_Size].m_Age = age;
        std::cout << "请输入年龄：" << std::endl;
        int age = 0;
        while (!(std::cin >> age))
        {
            std::cout << "输入有误，请重新输入年龄：" << std::endl;
            std::cin.clear();                                         // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空输入缓冲区
        }
        abs->personArray[abs->m_Size].m_Age = age;

        //联系电话
        std::cout << "请输入联系电话：" << std::endl;
        std::string iphone;
        std::cin >> iphone;
        abs->personArray[abs->m_Size].m_Phone = iphone;

        //家庭住址
        std::cout << "请输入家庭住址：" << std::endl;
        std::string address;
        std::cin >> address;
        abs->personArray[abs->m_Size].m_Addr = address;

        //更新通讯录人数
        abs->m_Size++;

        std::cout << "添加成功" << std::endl;
        system("pause");
        system("cls");
    }
}

//2、显示所有联系人信息
void showPerson(Addressbooks * abs)
{
    if (abs->m_Size == 0)
    {
        std::cout << "当前记录为空" << std::endl;
    }
    else
    {
        for (int i = 0; i < abs->m_Size; i++)
        {
            std::cout << "姓名：" << abs->personArray[i].m_Name << "\t";
            std::cout << "性别：" << (abs->personArray[i].m_Sex == '1' ? "男" : "女") << "\t";
            std::cout << "年龄：" << abs->personArray[i].m_Age << "\t";
            std::cout << "电话：" << abs->personArray[i].m_Phone << "\t";
            std::cout << "住址：" << abs->personArray[i].m_Addr << std::endl;
        }
    }

    system("pause");
    system("cls");

}

//判断是否存在查询的人员，存在返回在数组中索引位置，不存在返回-1
int isExist(Addressbooks * abs, const std::string& name)
{
    for (int i = 0; i < abs->m_Size; i++)
    {
        if (abs->personArray[i].m_Name == name)
        {
            return i;
        }
    }
    return -1;
}

//3、删除指定联系人信息
void deletePerson(Addressbooks * abs)
{
    std::cout << "请输入您要删除的联系人" << std::endl;
    std::string name;
    std::cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        for (int i = ret; i < abs->m_Size; i++)
        {
            abs->personArray[i] = abs->personArray[i + 1];
        }
        abs->m_Size--;
        std::cout << "删除成功" << std::endl;
    }
    else
    {
        std::cout << "查无此人" << std::endl;
    }

    system("pause");
    system("cls");
}

//4、查找指定联系人信息
void findPerson(Addressbooks * abs)
{
    std::cout << "请输入您要查找的联系人" << std::endl;
    std::string name;
    std::cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        std::cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
        std::cout << "性别：" << abs->personArray[ret].m_Sex << "\t";
        std::cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
        std::cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
        std::cout << "住址：" << abs->personArray[ret].m_Addr << std::endl;
    }
    else
    {
        std::cout << "查无此人" << std::endl;
    }

    system("pause");
    system("cls");

}

//5、修改指定联系人信息
void modifyPerson(Addressbooks * abs)
{
    std::cout << "请输入您要修改的联系人" << std::endl;
    std::string name;
    std::cin >> name;

    int ret = isExist(abs, name);
    if (ret != -1)
    {
        //姓名
        std::string iname;
        std::cout << "请输入姓名：" << std::endl;
        std::cin >> iname;
        abs->personArray[ret].m_Name = iname;

        std::cout << "请输入性别：" << std::endl;
        std::cout << "1 -- 男" << std::endl;
        std::cout << "2 -- 女" << std::endl;

        //性别
        std::string sex = "0";
        while (true)
        {
            std::cin >> sex;
            if (sex[0] == '1' || sex[0] == '2')
            {
                abs->personArray[ret].m_Sex = sex[0];
                break;
            }
            std::cout << "输入有误，请重新输入";
        }

        //年龄
        std::cout << "请输入年龄：" << std::endl;
        int age = 0;
        std::cin >> age;
        abs->personArray[ret].m_Age = age;

        //联系电话
        std::cout << "请输入联系电话：" << std::endl;
        std::string phone;
        std::cin >> phone;
        abs->personArray[ret].m_Phone = phone;

        //家庭住址
        std::cout << "请输入家庭住址：" << std::endl;
        std::string address;
        std::cin >> address;
        abs->personArray[ret].m_Addr = address;

        std::cout << "修改成功" << std::endl;
    }
    else
    {
        std::cout << "查无此人" << std::endl;
    }

    system("pause");
    system("cls");

}

//6、清空所有联系人
void cleanPerson(Addressbooks * abs)
{
    abs->m_Size = 0;
    std::cout << "通讯录已清空" << std::endl;
    system("pause");
    system("cls");
}

