#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>
#include <fstream>
#include <sstream>

// Hàm để thực thi một lệnh shell và ghi lại đầu ra của nó; người gọi có trách nhiệm giải phóng bộ nhớ
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int KEY_LENGTH = 2048; // Độ dài khóa DSA
    
    // Tạo tệp tạm thời cho tham số DSA
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // Tạo tệp tạm thời cho khóa DSA
    char key_filename[] = "/tmp/dsa_key_XXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        remove(param_filename);
        return "";
    }
    close(fd);
    
    try {
        // Bước 1: Tạo tham số DSA
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(KEY_LENGTH);
        std::string param_output = execute_command(param_command);
        
        // Kiểm tra xem lệnh có thành công không
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos ||
            param_output.find("ERROR") != std::string::npos) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        // Bước 2: Tạo khóa DSA riêng từ tham số
        std::string key_command = "openssl gendsa " + std::string(param_filename) + 
                                 " -out " + std::string(key_filename);
        std::string key_output = execute_command(key_command);
        
        // Kiểm tra xem lệnh có thành công không
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos ||
            key_output.find("ERROR") != std::string::npos) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        // Đọc nội dung khóa từ tệp
        std::ifstream key_file(key_filename);
        if (!key_file.is_open()) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        std::stringstream key_stream;
        key_stream << key_file.rdbuf();
        std::string private_key = key_stream.str();
        
        // Xóa các tệp tạm thời
        remove(param_filename);
        remove(key_filename);
        
        // Kiểm tra xem khóa có hợp lệ không
        if (private_key.empty() || private_key.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
        return private_key;
        
    } catch (const std::exception& e) {
        // Dọn dẹp tệp tạm thời trong trường hợp có ngoại lệ
        remove(param_filename);
        remove(key_filename);
        return "";
    }
}