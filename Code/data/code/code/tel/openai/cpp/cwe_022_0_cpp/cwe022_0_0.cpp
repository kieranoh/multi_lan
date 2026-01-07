#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file.is_open()) {
        return "";
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n';
    }

    file.close();
    return content;
}