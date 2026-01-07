#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Tạo tên tệp tạm thời
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Trả về chuỗi rỗng nếu không thể tạo tệp tạm thời
    }
    
    // Đóng tệp sau khi tạo
    close(fd);

    // Độ dài khóa DSA, ví dụ 2048
    const int key_length = 2048;

    // Tạo tham số DSA
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (!execute_command(param_command)) {
        unlink(param_filename); // Xóa tệp nếu có lỗi
        return ""; // Trả về chuỗi rỗng nếu có lỗi
    }

    // Tạo khóa DSA từ tham số
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    // Xóa tệp tạm thời
    unlink(param_filename);

    return private_key; // Trả về khóa DSA riêng
}