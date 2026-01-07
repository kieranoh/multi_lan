#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Create full path by combining directory path and filename
    std::filesystem::path full_path = std::filesystem::path(dir_path) / filename;
    
    // Check if the file exists and is a regular file
    std::error_code ec;
    if (!std::filesystem::exists(full_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(full_path, ec) || ec) {
        return "";
    }
    
    // Try to open and read the file
    std::ifstream file(full_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // Read the entire file content
    std::string content;
    file.seekg(0, std::ios::end);
    content.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    
    content.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    
    // Check for read errors
    if (file.fail() && !file.eof()) {
        return "";
    }
    
    return content;
}