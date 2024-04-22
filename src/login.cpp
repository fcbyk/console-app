#include "../include/main.h"

int login() {

    std::string username, password;

    // 验证用户名
    while (true) {
        std::cout << "请输入用户名: ";
        getline(std::cin, username);
        if (username.empty()) std::cout << "输入为空，请重新输入" << std::endl;
        else if (username != "admin") std::cout << "不存在该用户名，请重新输入" << std::endl;
        else break;
    }

    // 验证密码
    while (true) {

        std::cout << "请输入" << username << "的密码:";
        getline(std::cin, password);
        if (password.empty()) std::cout << "输入为空，请重新输入" << std::endl;
        else if (password != "123456") std::cout << "密码错误，请重新输入" << std::endl;
        else {
            std::cout << "登录成功" << std::endl;
            system("pause");
            return 1;
        }
    }

}

