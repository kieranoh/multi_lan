#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Command to execute
    std::string command = "ls -l " + dir_path;

    // Buffer to hold the command output
    std::array<char, 128> buffer;
    std::string result;

    // Create a pipe to read output from the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if the command executed successfully
    if (result.empty() && !feof(pipe.get())) {
        return ""; // Return empty string if there was an error
    }

    return result; // Return the command output
}