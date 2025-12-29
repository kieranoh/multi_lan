#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;
    
    // Open the command for reading.
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string if the pipe couldn't be opened
    }
    
    // Read the output a line at a time - output it.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check for errors or if the result is empty
    if (result.empty()) {
        return ""; // Return empty string on error
    }
    
    return result; // Return the result of the command
}