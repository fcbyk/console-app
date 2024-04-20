#include "../include/main.h"

int login() {

    string username, password;

    // 验证用户名
    while (true) {
        cout << "请输入用户名: ";
        getline(cin, username);
        if (username.empty()) cout << "输入为空，请重新输入" << endl;
        else if (username != "admin") cout << "不存在该用户名，请重新输入" << endl;
        else break;
    }

    // 验证密码
    while (true) {

        cout << "请输入" << username << "的密码:";
        getline(cin, password);
        if (password.empty()) cout << "输入为空，请重新输入" << endl;
        else if (password != "123456") cout << "密码错误，请重新输入" << endl;
        else {
            cout << "登录成功" << endl;
            system("pause");
            return 1;
        }
    }

}

