#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::ifstream file(dir_path + "/" + filename);
    if (!file.is_open()) {
        return ""; // Return an empty string if the file cannot be opened
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file content into the buffer
    return buffer.str(); // Return the content of the file
}