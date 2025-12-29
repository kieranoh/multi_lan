#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 确保目录存在
    std::filesystem::create_directories(directory);
    
    // 组合完整文件路径
    std::string filePath = directory + "/" + filename;
    
    // 创建并写入文件
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        
        // 设置文件权限，仅当前用户可访问
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        std::cerr << "无法打开文件: " << filePath << std::endl;
    }
}