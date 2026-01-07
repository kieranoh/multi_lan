#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Tạo đường dẫn đầy đủ cho tệp
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Tạo thư mục nếu nó chưa tồn tại
    std::filesystem::create_directories(directory);

    // Lưu nội dung vào tệp
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << content;
        outFile.close();

        // Đặt quyền truy cập cho tệp chỉ cho người dùng hiện tại
        uid_t userId = getuid();
        gid_t groupId = getgid();
        chown(filePath.c_str(), userId, groupId);
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR); // chỉ cho phép người dùng hiện tại đọc và ghi
    } else {
        std::cerr << "Không thể mở tệp để ghi: " << filePath << std::endl;
    }
}