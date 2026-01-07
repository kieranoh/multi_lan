#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Create a command string for executing ls -l on the provided directory path
    std::string command = "ls -l " + dir_path;

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    
    // Check if the pipe is successfully opened
    if (!pipe) {
        return ""; // Return empty string on error
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result; // Return the result of ls -l command
}