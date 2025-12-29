#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;
    
    // Use popen to execute the command and read the output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}