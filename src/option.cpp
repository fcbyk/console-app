#include "../include/main.h"

int option(int argc, char *argv[]){

    std::map<std::string, std::string> opt;

    // 从命令行参数中提取键值对，并保存到 map 中
    for (int i = 1; i < argc; i += 2) if (i + 1 < argc)  opt[argv[i]] = argv[i + 1];

    if (opt.empty() && (std::string(argv[1]) =="-v" || std::string(argv[1]) =="-version")){
        std::cout << "console-app v0.0.1-alpha" << std::endl;
        std::cout << "https://github.com/fcbyk/console-app" << std::endl;
    } else if (opt.size()==2){
        auto username = opt.find("-u");
        auto password = opt.find("-p");
        if (username != opt.end() && password != opt.end()) {
            // 检查用户名和密码是否匹配
            if (username->second == "admin" && password->second == "123456") {
                return 1; // 登录成功
            } else {
                std::cout << "不存在用户名，或者密码错误" << std::endl;
            }
        }
    } else{
        std::cout << " 找不到该选项，请输入正确选项" << std::endl;
        std::cout << " [ -v | -version]  查看系统版本" << std::endl;
        std::cout << " -u  <用户名> -p <密码>  登录系统" << std::endl;
        std::cout << " 不输入任何选项可直接进入登录设置" << std::endl;
    }

    return 0;
}

