#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file) {
        return "";
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}