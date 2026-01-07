#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    std::string result;
    std::array<char, 128> buffer;
    
    // Create the command to execute
    std::string command = "ls -l " + dir_path + " 2>/dev/null"; // Redirect stderr to /dev/null
    
    // Open a pipe to run the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}