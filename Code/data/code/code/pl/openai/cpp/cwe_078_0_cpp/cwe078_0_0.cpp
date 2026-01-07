#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Prepare the command to execute
    std::string command = "ls -l " + dir_path;

    // Use a pipe to get the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Create a process to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string in case of error
    }

    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Return the result of the command
}