#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Prepare the command to be executed
    std::string command = "ls -l " + dir_path;

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

    // Check if the pipe opened successfully
    if (!pipe) {
        return ""; // Return an empty string if the pipe could not be opened
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Return the collected output
}