#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Prepare the command to be executed
    std::string command = "ls -l " + dir_path;
    
    // Create a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;

    // Using popen to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error
    }

    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // Append the output to result
    }

    return result; // Return the gathered output
}