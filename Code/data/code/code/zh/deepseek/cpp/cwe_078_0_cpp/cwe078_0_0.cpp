#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // 构建命令字符串，使用 -l 选项并指定目录路径
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // 打开管道以读取命令输出
    std::array<char, 128> buffer;
    std::string result;
    
    // 使用 popen 执行命令并读取输出
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 如果无法打开管道，返回空字符串
        return "";
    }
    
    // 读取命令输出
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 检查命令是否成功执行（通过检查输出是否为空）
    // 注意：ls -l 在空目录中会输出 "total 0"，所以空结果可能表示错误
    // 但 popen 的退出状态无法直接获取，所以我们依赖 2>/dev/null 重定向错误
    
    // 如果结果为空，返回空字符串（表示错误）
    if (result.empty()) {
        return "";
    }
    
    return result;
}