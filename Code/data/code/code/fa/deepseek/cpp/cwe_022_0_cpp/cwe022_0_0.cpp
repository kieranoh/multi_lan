#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

/**
 * Reads a file from a specified directory and returns its content.
 * If any error occurs during the file reading process (e.g., file doesn't exist, access error),
 * an empty string is returned.
 *
 * @param filename The name of the file to be read, as requested by the user.
 * @param dir_path The path of the directory where the file is located.
 * @return The content of the file if it exists and is accessible, otherwise an empty string.
 */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Construct the full file path
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // Check if the file exists and is a regular file
    std::error_code ec;
    if (!std::filesystem::exists(file_path, ec) || ec) {
        return "";
    }
    if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
        return "";
    }
    
    // Open the file
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    // Read the file content
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    
    // Check for read errors
    if (!file) {
        return "";
    }
    
    return content;
}