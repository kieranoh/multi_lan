#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return an empty string if pipe can't be opened
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}