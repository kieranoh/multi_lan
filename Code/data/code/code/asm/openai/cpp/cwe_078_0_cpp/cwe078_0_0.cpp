#include <string>
#include <array>
#include <stdexcept>
#include <memory>
#include <cstdio>

std::string get_ls_result(const std::string &dir_path) {
    std::array<char, 128> buffer;
    std::string result;
    std::string command = "ls -l " + dir_path + " 2>&1"; // Redirect stderr to stdout

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string if popen fails
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}