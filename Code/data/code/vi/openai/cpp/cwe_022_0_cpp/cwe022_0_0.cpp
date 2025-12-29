#include <iostream>
#include <fstream>
#include <string>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file) {
        // Nếu không thể mở tệp, trả về chuỗi rỗng
        return "";
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Thêm dấu xuống dòng sau mỗi dòng
    }

    file.close();
    return content;
}