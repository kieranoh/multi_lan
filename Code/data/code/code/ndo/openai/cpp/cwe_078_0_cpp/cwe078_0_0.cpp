#include <iostream>
#include <string>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;
    
    // Open a pipe to the command and read its output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on pipe failure
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}