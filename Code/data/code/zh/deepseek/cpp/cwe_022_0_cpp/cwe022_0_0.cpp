#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // 使用 std::filesystem 构建完整的文件路径
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // 检查文件是否存在且可访问
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    // 检查是否为常规文件
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // 尝试打开文件
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return "";
    }
    
    // 获取文件大小
    std::streamsize size = file.tellg();
    if (size == -1) {
        return "";
    }
    
    // 重置文件指针到开头
    file.seekg(0, std::ios::beg);
    
    // 读取文件内容
    std::string content;
    content.resize(size);
    
    if (!file.read(&content[0], size)) {
        return "";
    }
    
    return content;
}