#include <string>
#include <fstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Construct the full file path
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Check if the file exists and is a regular file
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Open the file for reading
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return "";
        }
        
        // Get the file size
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Read the entire file content
        std::string content;
        content.resize(size);
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
    }
    catch (...) {
        // Catch any exceptions (permission errors, filesystem errors, etc.)
        return "";
    }
}