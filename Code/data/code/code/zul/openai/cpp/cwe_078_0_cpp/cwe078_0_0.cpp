#include <iostream>
#include <string>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Command to execute
    std::string command = "ls -l " + dir_path;

    // Create a buffer to read the command's output
    std::array<char, 128> buffer;
    std::string result;

    // Open the command for reading
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // If the pipe cannot be opened, return an empty string
        return "";
    }
    
    // Read the output a line at a time - output it.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result; // Return the command output
}