#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Construct the full path to the file
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // Try to open the file
    std::ifstream file(file_path);
    
    // Check if the file is open
    if (!file.is_open()) {
        return ""; // Return an empty string if the file cannot be opened
    }

    // Read the contents of the file into a string
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    // Close the file and return the content
    file.close();
    return content;
}