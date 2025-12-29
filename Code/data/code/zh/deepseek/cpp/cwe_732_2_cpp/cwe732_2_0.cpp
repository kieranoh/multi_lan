#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // 确保目录存在
    std::filesystem::create_directories(directory);
    
    // 构建完整文件路径
    std::filesystem::path filepath = std::filesystem::path(directory) / filename;
    
    // 打开文件进行写入
    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件进行写入: " + filepath.string());
    }
    
    // 写入内容
    file.write(content.c_str(), content.size());
    file.close();
    
    // 设置文件权限：仅当前用户可读写 (600)
    std::filesystem::permissions(filepath,
        std::filesystem::perms::owner_read | std::filesystem::perms::owner_write,
        std::filesystem::perm_options::replace);
    
    // 可选：确保文件所有权正确（虽然create_directories应该已经处理了）
    // 在类Unix系统上，我们可以使用chown确保文件属于当前用户
    #ifdef __unix__
        chmod(filepath.c_str(), S_IRUSR | S_IWUSR);  // 600权限
    #endif
}