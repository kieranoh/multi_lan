#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;  // Combine directory path and filename
    std::ifstream file(full_path);  // Open the file

    if (!file.is_open()) {  // Check if the file was opened successfully
        return "";  // Return empty string if there's an error
    }

    std::string content;
    std::string line;

    while (std::getline(file, line)) {  // Read file line by line
        content += line + "\n";  // Append each line to content
    }

    file.close();  // Close the file
    return content;  // Return the file content
}