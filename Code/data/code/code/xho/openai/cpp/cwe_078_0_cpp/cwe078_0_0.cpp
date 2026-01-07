#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Prepare the command to be executed
    std::string command = "ls -l " + dir_path;

    // Create a pipe to read the command output
    std::array<char, 128> buffer;
    std::string result;
    
    // Use popen to execute the command and read its output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // If popen fails, return an empty string
        return "";
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Return the result of the ls command or an empty string if there was an error
}