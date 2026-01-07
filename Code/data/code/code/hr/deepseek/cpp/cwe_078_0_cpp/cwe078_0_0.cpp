#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Konstruiraj naredbu s pravilnim escapiranjem puta
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Otvori pipe za čitanje izlaza naredbe
    std::array<char, 128> buffer;
    std::string result;
    
    // Otvori proces za izvršenje naredbe
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // Provjeri je li pipe uspješno otvoren
    if (!pipe) {
        return "";
    }
    
    // Pročitaj izlaz naredbe
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Provjeri je li naredba uspješno izvršena
    int status = pclose(pipe.release());
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return result;
    } else {
        return "";
    }
}