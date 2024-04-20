#include "include/main.h"

int main() {

    // 控制台切换为 UTF-8 编码，解决控制台乱码问题
    system("chcp 65001 > nul");

    login();
    cout << "程序正常执行" << endl;
    system("pause");
    return 0;
}
