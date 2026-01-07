#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;
    
    // 使用管道执行命令并读取输出
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // 如果管道创建失败，返回空字符串
    }

    // 读取命令的输出
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}