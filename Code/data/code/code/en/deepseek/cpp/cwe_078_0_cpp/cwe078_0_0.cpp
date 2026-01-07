#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Construct the command with proper quoting for the directory path
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Open a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Use popen to execute the command and capture stdout
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // Check if pipe opened successfully
    if (!pipe) {
        // If popen fails, return empty string
        return "";
    }
    
    // Read the output from the pipe
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Check if the command executed successfully by checking the exit status
    // We need to get the exit status from pclose
    // Since we already called pclose in the unique_ptr deleter, we need to check differently
    // We'll check if result is empty, which could indicate an error
    // However, an empty result could also mean the directory is empty
    // So we need to verify the directory exists and is accessible
    
    // We'll run a separate check to see if the directory is accessible
    // by trying to list it with a simple ls command that returns exit code
    std::string check_cmd = "ls \"" + dir_path + "\" >/dev/null 2>&1";
    int check_status = system(check_cmd.c_str());
    
    // If the check command failed (non-zero exit status), return empty string
    if (check_status != 0) {
        return "";
    }
    
    return result;
}