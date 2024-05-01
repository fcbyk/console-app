#ifndef CONSOLE_APP_FUNCTION_H
#define CONSOLE_APP_FUNCTION_H
#endif

#include "../include/common_libs.h"
#include "./app/addressBook.h"
#include "./app/WorkerManager.h"
#include "./app/SpeechManager.h"
#include "./app/ComputerRoomReservation.h"

// 登录验证
int login();

// 程序启动选项
int option(int argc, char *argv[]);

// 命令行操作
int terminal(const std::string& user);