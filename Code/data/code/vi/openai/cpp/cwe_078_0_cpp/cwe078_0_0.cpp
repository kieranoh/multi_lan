#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Command to execute
    std::string command = "ls -l " + dir_path;
    
    // Array to hold the output of the command
    std::array<char, 128> buffer;
    std::string result;

    // Create a pipe to read the output of the command
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return an empty string on error
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // Append the output to the result string
    }

    return result; // Return the final output
}