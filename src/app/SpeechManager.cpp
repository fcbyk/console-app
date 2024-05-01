#include "./../../include/app/SpeechManager.h"

int SpeechManager::SpeechManagerLaunch(){
    srand((unsigned int)time(NULL));

//    测试代码
//    for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
//    {
//        std::cout  << "选手编号：" << it->first
//              << " 姓名： " << it->second.m_Name
//              << " 成绩： " << it->second.m_Score[0] << std::endl;
//    }

    int choice = 0; //用来存储用户的选项

    bool shouldExit = false; // 控制外部 while 循环的变量

    while (!shouldExit)
    {
        this->show_Menu();

        std::cout << "请输入您的选择： " << std::endl;
        std::cin >> choice; // 接受用户的选项

        switch (choice)
        {
            case 1:  //开始比赛
                this->startSpeech();
                break;
            case 2:  //查看记录
                this->showRecord();
                break;
            case 3:  //清空记录
                this->clearRecord();
                break;
            case 0:  //退出系统
                this->exitSystem();
                shouldExit = true;
                getchar();
                break;
            default:
                system("cls"); //清屏
                break;
        }
    }
    system("pause");
    return 0;
}

SpeechManager::SpeechManager()
{
    //初始化属性
    this->initSpeech();

    //创建选手
    this->createSpeaker();

    //获取往届记录
    this->loadRecord();
}

SpeechManager::~SpeechManager()
{
}

void SpeechManager::show_Menu()
{
    std::cout << " ----------------------------------------" << std::endl;
    std::cout << "|            欢迎参加演讲比赛            |" << std::endl;
    std::cout << "|            1.开始演讲比赛              |" << std::endl;
    std::cout << "|            2.查看往届记录              |" << std::endl;
    std::cout << "|            3.清空比赛记录              |" << std::endl;
    std::cout << "|            0.退出比赛程序              |" << std::endl;
    std::cout << " ----------------------------------------" << std::endl;
    std::cout << std::endl;
}

void SpeechManager::exitSystem()
{
    std::cout << "欢迎下次使用" << std::endl;
//    system("pause");
//    exit(0);
}

void SpeechManager::initSpeech()
{
    //容器保证为空
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();
    //初始化比赛轮数
    this->m_Index = 1;

    this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
    std::string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++)
    {
        std::string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.m_Name = name;
        for (int i = 0; i < 2; i++)
        {
            sp.m_Score[i] = 0;
        }

        //12名选手编号
        this->v1.push_back(i + 10001);

        //选手编号 以及对应的选手 存放到map容器中
        this->m_Speaker.insert(std::make_pair(i + 10001, sp));
    }
}

void SpeechManager::speechDraw()
{
    std::cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签"<<std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "抽签后演讲顺序如下：" << std::endl;
    if (this->m_Index == 1)
    {
        random_shuffle(v1.begin(), v1.end());
        for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        random_shuffle(v2.begin(), v2.end());
        for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;
    system("pause");
    std::cout << std::endl;
}

void SpeechManager::speechContest()
{
    std::cout << "------------- 第"<< this->m_Index << "轮正式比赛开始：------------- " << std::endl;

    std::multimap<double, int, std::greater<int>> groupScore; //临时容器，保存key分数 value 选手编号

    int num = 0; //记录人员数，6个为1组

    std::vector <int>v_Src;   //比赛的人员容器
    if (this->m_Index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }

    //遍历所有参赛选手
    for (std::vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
    {
        num++;

        //评委打分
        std::deque<double>d;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
            //std::cout << score << " ";
            d.push_back(score);
        }

        sort(d.begin(), d.end(), std::greater<double>());				//排序
        d.pop_front();												//去掉最高分
        d.pop_back();												//去掉最低分

        double sum = accumulate(d.begin(), d.end(), 0.0f);				//获取总分
        double avg = sum / (double)d.size();									//获取平均分

        //每个人平均分
        //std::cout << "编号： " << *it  << " 选手： " << this->m_Speaker[*it].m_Name << " 获取平均分为： " << avg << std::endl;  //打印分数
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

        //6个人一组，用临时容器保存
        groupScore.insert(std::make_pair(avg, *it));
        if (num % 6 == 0)
        {

            std::cout << "第" << num / 6 << "小组比赛名次：" << std::endl;
            for (std::multimap<double, int, std::greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                std::cout << "编号: " << it->second << " 姓名： " << this->m_Speaker[it->second].m_Name << " 成绩： " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << std::endl;
            }

            int count = 0;
            //取前三名
            for (std::multimap<double, int, std::greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vVictory.push_back((*it).second);
                }
            }

            groupScore.clear();

            std::cout << std::endl;

        }
    }
    std::cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << std::endl;
    system("pause");
}

void SpeechManager::showScore()
{
    std::cout << "---------第" << this->m_Index << "轮晋级选手信息如下：-----------" << std::endl;
    std::vector<int>v;
    if (this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = vVictory;
    }

    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::cout << "选手编号：" << *it << " 姓名： " << m_Speaker[*it].m_Name << " 得分： " << m_Speaker[*it].m_Score[this->m_Index - 1] << std::endl;
    }
    std::cout << std::endl;

    system("pause");
    system("cls");
    this->show_Menu();
}

void SpeechManager::saveRecord()
{
    std::ofstream ofs;
    ofs.open("speech.csv", std::ios::out | std::ios::app); // 用输出的方式打开文件  -- 写文件

    //将每个人数据写入到文件中
    for (std::vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
    {
        ofs << *it << ","
            << m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << std::endl;

    //关闭文件
    ofs.close();

    std::cout << "记录已经保存" << std::endl;

    this->fileIsEmpty = false;
}

//开始比赛
void SpeechManager::startSpeech()
{
    //第一轮比赛
    //1、抽签
    speechDraw();

    //2、比赛
    speechContest();

    //3、显示晋级结果
    showScore();

    //第二轮比赛
    this->m_Index++;

    //1、抽签
    speechDraw();

    //2、比赛
    speechContest();

    //3、显示最终结果
    showScore();

    //4、保存分数
    saveRecord();

    //重置比赛
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();

    std::cout << "本届比赛完毕!" << std::endl;
    system("pause");
    system("cls");
}

void SpeechManager::loadRecord()
{
    std::ifstream ifs("speech.csv", std::ios::in); //输入流对象 读取文件

    if (!ifs.is_open())
    {
        this->fileIsEmpty = true;
        std::cout << "文件不存在！" << std::endl;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        std::cout << "文件为空!" << std::endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件不为空
    this->fileIsEmpty = false;

    ifs.putback(ch); //读取的单个字符放回去

    std::string data;
    int index = 0;
    while (ifs >> data)
    {
        //std::cout << data << std::endl;
        std::vector<std::string>v;

        int pos = -1;
        int start = 0;

        while (true)
        {
            pos = data.find(",", start); //从0开始查找 ','
            if (pos == -1)
            {
                break; //找不到break返回
            }
            std::string tmp = data.substr(start, pos - start); //找到了,进行分割 参数1 起始位置，参数2 截取长度
            v.push_back(tmp);
            start = pos + 1;
        }

        this->m_Record.insert(make_pair(index, v));
        index++;
    }

    ifs.close();
}

void SpeechManager::showRecord()
{
    if(this->fileIsEmpty)
    {
        std::cout << "文件不存在，或记录为空" << std::endl;
    }
    else
    {
        for (int i = 0; i < this->m_Record.size(); i++)
        {
            std::cout << "第" << i + 1 << "届 " <<
                 "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
                 "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
                 "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << std::endl;
        }
    }
    system("pause");
    system("cls");
}

void SpeechManager::clearRecord()
{
    std::cout << "确认清空？" << std::endl;
    std::cout << "1、确认" << std::endl;
    std::cout << "2、返回" << std::endl;

    int select = 0;
    std::cin >> select;

    if (select == 1)
    {
        //打开模式 std::ios::trunc 如果存在删除文件并重新创建
        std::ofstream ofs("speech.csv", std::ios::trunc);
        ofs.close();

        //初始化属性
        this->initSpeech();

        //创建选手
        this->createSpeaker();

        //获取往届记录
        this->loadRecord();


        std::cout << "清空成功！" << std::endl;
    }

    system("pause");
    system("cls");
}

