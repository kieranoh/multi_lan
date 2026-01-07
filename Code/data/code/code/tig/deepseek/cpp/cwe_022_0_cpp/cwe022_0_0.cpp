#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    std::ifstream file_stream(file_path, std::ios::in | std::ios::binary);
    if (!file_stream.is_open()) {
        return "";
    }
    
    file_stream.seekg(0, std::ios::end);
    std::streamsize file_size = file_stream.tellg();
    file_stream.seekg(0, std::ios::beg);
    
    if (file_size <= 0) {
        return "";
    }
    
    std::string content;
    content.resize(static_cast<size_t>(file_size));
    
    if (!file_stream.read(&content[0], file_size)) {
        return "";
    }
    
    return content;
}