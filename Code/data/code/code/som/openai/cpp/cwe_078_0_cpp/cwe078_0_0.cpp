#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    std::array<char, 128> buffer;
    std::string result;
    std::string command = "ls -l " + dir_path + " 2>&1"; // Redirect stderr to stdout

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // If the pipe could not be opened, return empty string
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // Read output from command
    }

    if (result.empty() || result.find("No such file or directory") != std::string::npos || 
        result.find("Permission denied") != std::string::npos) {
        return ""; // Return empty string on errors
    }

    return result; // Return the result of the command
}