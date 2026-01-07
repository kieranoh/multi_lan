#include <iostream>
#include <fstream>
#include <string>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Combine directory path and filename to create the full file path
    std::string full_path = dir_path + "/" + filename;
    
    // Open the file
    std::ifstream file(full_path);
    
    // Check if the file was opened successfully
    if (!file.is_open()) {
        return ""; // Return empty string if the file cannot be opened
    }
    
    // Read the contents of the file
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Append each line to content with a newline character
    }
    
    // Close the file
    file.close();
    
    return content; // Return the content of the file
}