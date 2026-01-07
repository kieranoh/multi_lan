#include <iostream>
#include <string>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Create a command string to execute 'ls -l' in the provided directory
    std::string command = "ls -l " + dir_path;

    // Use popen to execute the command and read the output
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

    // Check if the pipe was created successfully
    if (!pipe) {
        return ""; // Return an empty string if the command execution fails
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // Append the output to the result string
    }

    return result; // Return the result of the 'ls -l' command
}