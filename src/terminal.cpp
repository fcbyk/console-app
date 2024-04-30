#include "../include/main.h"

int terminal(const std::string& user){
    std::string command;
    while (true){
        std::cout << user << "# ";
        getline(std::cin, command);
        if(command == "clear") system("cls");
        else if (command.empty()) continue;
        else if (command == "help")
            std::cout
                    << "clear 清除屏幕" << std::endl
                    << "open 打开app，空格后接app名称" << std::endl
                    << "exit 退出系统" << std::endl;
        else if (command == "exit") break;
        else std::cout << "请输入有效指令，使用help指令可查看使用帮助" << std::endl;
    }
    return 0;
}
