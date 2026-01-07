#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Prepare the command to execute
    std::string command = "ls -l " + dir_path;

    // Create a buffer to hold the command output
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // Return empty string if pipe could not be opened
        return "";
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Return the result or an empty string if there was an error
    return result.empty() ? "" : result;
}