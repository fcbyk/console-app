# 设置CMake脚本的最低版本要求
cmake_minimum_required(VERSION 3.17)

# 项目的名称
project(console_app)

# 设置C++标准的版本,使用C++20标准来编译源代码
set(CMAKE_CXX_STANDARD 20)

# 设置构建的可执行文件的名称
# 设置构建可执行文件所需的源代码文件
add_executable(
        console_app
        main.cpp
        src/login.cpp
        include/common_libs.h
        include/main.h
        src/option.cpp
        src/terminal.cpp
        include/app/addressBook.h
        src/app/addressBook.cpp
        include/app/WorkerManager.h
        src/app/WorkerManager.cpp
        include/app/SpeechManager.h
        src/app/SpeechManager.cpp
        )

# 静态链接C++标准库
target_link_libraries(console_app -static-libstdc++ -static-libgcc)