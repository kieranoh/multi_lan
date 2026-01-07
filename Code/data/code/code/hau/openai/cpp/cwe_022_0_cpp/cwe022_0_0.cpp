#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::ifstream file;
    std::string full_path = dir_path + "/" + filename;

    // Try to open the file
    file.open(full_path);
    
    // Check if the file was opened successfully
    if (!file.is_open()) {
        return ""; // Return an empty string if the file cannot be opened
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read file content into the stringstream
    file.close(); // Close the file

    return buffer.str(); // Return the file content as a string
}