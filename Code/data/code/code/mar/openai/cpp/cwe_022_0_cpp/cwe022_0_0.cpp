#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // Build the full file path
    std::ifstream file(full_path); // Open the file

    // Check if the file opening was successful
    if (!file.is_open()) {
        return ""; // Return empty string on error
    }

    std::string content;
    std::string line;

    // Read the file line by line
    while (std::getline(file, line)) {
        content += line + "\n"; // Append line to content
    }

    file.close(); // Close the file
    return content; // Return the file content
}