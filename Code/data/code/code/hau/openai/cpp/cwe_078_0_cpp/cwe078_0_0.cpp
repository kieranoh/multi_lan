#include <string>
#include <array>
#include <stdexcept>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // The command to be executed
    std::string command = "ls -l " + dir_path;

    // Using a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;

    // Create a process to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string on error
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data(); // Append the output to the result string
    }

    return result; // Return the output of the command
}