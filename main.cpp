#include "include/main.h"
#include <Windows.h>

int main(int argc, char *argv[]) {

    // 控制台切换为 UTF-8 编码，解决控制台乱码问题
    // system("chcp 65001 > nul");
    SetConsoleOutputCP(CP_UTF8);

    if(argc == 1) login();
    else if(!option(argc, argv)) return 0;

    std::cout << "程序正常执行" << std::endl;
    system("pause");
    return 0;
}