#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file) {
        return ""; // Return an empty string if the file cannot be opened
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Append each line to content with a newline
    }
    
    file.close(); // Close the file after reading
    return content; // Return the content of the file
}