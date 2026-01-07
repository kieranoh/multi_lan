#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // Create the full file path
    std::ifstream file(full_path); // Open the file

    if (!file) { // Check if the file opened successfully
        return ""; // Return an empty string on error
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file content into the buffer
    file.close(); // Close the file

    return buffer.str(); // Return the content of the file
}