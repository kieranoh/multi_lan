#include <iostream>
#include <string>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Create a command string for ls -l
    std::string command = "ls -l " + dir_path;

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return ""; // Return empty string if pipe creation failed
    }

    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Return the command output
}