#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Build the full path to the file
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;

    // Check if the file exists and is accessible
    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
        return ""; // Return empty string if the file does not exist
    }

    // Open the file and read its contents
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return ""; // Return empty string if the file cannot be opened
    }

    std::string content;
    std::string line;

    // Read the file line by line
    while (std::getline(file, line)) {
        content += line + '\n'; // Append each line to content
    }

    file.close(); // Close the file
    return content; // Return the file content
}