#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <cstdio>

std::string get_ls_result(const std::string &dir_path) {
    std::array<char, 128> buffer;
    std::string result;
    std::string command = "ls -l " + dir_path + " 2>&1"; // Redirect stderr to stdout

    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // If pipe opening fails, return empty string
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? "" : result; // Return result or empty string if no output
}