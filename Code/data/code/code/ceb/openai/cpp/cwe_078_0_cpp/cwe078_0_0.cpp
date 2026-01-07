#include <string>
#include <array>
#include <stdexcept>
#include <memory>
#include <cstdio>

std::string get_ls_result(const std::string &dir_path) {
    // Command to execute
    std::string command = "ls -l " + dir_path;

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    
    // Open the command for reading
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error opening pipe
    }

    // Read the output a line at a time
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Return the result
    return result;
}