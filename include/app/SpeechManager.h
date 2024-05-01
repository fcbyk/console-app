#ifndef CONSOLE_APP_SPEECHMANAGER_H
#define CONSOLE_APP_SPEECHMANAGER_H
#endif

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>
#include <ctime>

class Speaker
{
public:
    std::string m_Name;  //姓名
    double m_Score[2]; //分数  最多有两轮得分
};

//演讲管理类
class SpeechManager
{
public:

    //构造函数
    SpeechManager();

    //析构函数
    ~SpeechManager();

    int SpeechManagerLaunch();

    void show_Menu();

    void exitSystem();

    //比赛选手 容器  12人
    std::vector<int>v1;

    //第一轮晋级容器  6人
    std::vector<int>v2;

    //胜利前三名容器  3人
    std::vector<int>vVictory;

    //存放编号 以及对应的 具体选手 容器
    std::map<int, Speaker> m_Speaker;

    //初始化属性
    void initSpeech();

    int m_Index;

    //初始化创建12名选手
    void createSpeaker();

    //开始比赛 - 比赛流程控制
    void startSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //显示比赛结果
    void showScore();

    //保存记录
    void saveRecord();

    //读取记录
    void loadRecord();

    //文件为空的标志
    bool fileIsEmpty;

    //往届记录
    std::map<int, std::vector<std::string>> m_Record;

    //显示往届得分
    void showRecord();

    //清空记录
    void clearRecord();
};
