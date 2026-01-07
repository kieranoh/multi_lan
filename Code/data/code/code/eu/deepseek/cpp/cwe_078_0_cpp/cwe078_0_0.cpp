#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstring>

std::string get_ls_result(const std::string &dir_path) {
    // Komandoa prestatu, direktorio bidea segurtasunez tratatuz
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Komandoa exekutatu eta irteera irakurri
    std::array<char, 128> buffer;
    std::string result;
    
    // popen erabili komandoa exekutatzeko
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // popen huts egin du
        return "";
    }
    
    // Irteera irakurri
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Irteera hutsa bada edo errore bat izan bada, string hutsa itzuli
    if (result.empty() || result.find("No such file or directory") != std::string::npos) {
        return "";
    }
    
    return result;
}