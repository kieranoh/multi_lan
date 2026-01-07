#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Combine the directory path and filename to create the full path
    std::string full_path = dir_path + "/" + filename;

    // Try to open the file
    std::ifstream file(full_path);
    
    // Check if the file is successfully opened
    if (!file.is_open()) {
        return ""; // Return an empty string if there was an error
    }

    std::string content;
    std::string line;

    // Read the file line by line
    while (std::getline(file, line)) {
        content += line + "\n"; // Append each line to the content
    }

    file.close(); // Close the file
    return content; // Return the file content
}