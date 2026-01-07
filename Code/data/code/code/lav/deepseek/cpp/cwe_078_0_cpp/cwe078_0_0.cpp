#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Construct the command with the directory path
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Open a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Use popen to execute the command and capture stdout
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Failed to open pipe, return empty string
        return "";
    }
    
    // Read the output a chunk at a time
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Check if the command executed successfully by checking pclose status
    int status = pclose(pipe.release());
    if (status != 0) {
        // Command failed (directory not found, permission error, etc.)
        return "";
    }
    
    return result;
}