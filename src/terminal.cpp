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
                    << "app 显示当前已安装的app" << std::endl
                    << "open 打开app，空格后接app名称" << std::endl
                    << "exit 退出系统" << std::endl;
        else if (command == "app")
            std::cout
                    << "目前已安装的APP列表" << std::endl
                    << "APP1：AddressBook" << std::endl
                    << "APP2：WorkerManager" << std::endl
                    << "(使用open + APP名称 可直接打开,注意区分大小写)" << std::endl;
        else if (command == "open AddressBook" || command == "open app1"){
            AddressBookLaunch();
        }
        else if (command == "open WorkerManager" || command == "open app2"){
            WorkerManager wm;
            wm.WorkerManagerLaunch();
        }
        else if (command == "exit") break;
        else std::cout << "请输入有效指令，使用help指令可查看使用帮助" << std::endl;
    }
    return 0;
}
