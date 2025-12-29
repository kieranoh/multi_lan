#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // Nejprve ověřte, zda cesta existuje a je to adresář
    try {
        if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
            return "";
        }
    } catch (const std::filesystem::filesystem_error&) {
        return "";
    } catch (...) {
        return "";
    }

    // Sestavte příkaz s bezpečným escapováním
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Otevřete potrubí pro čtení výstupu příkazu
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return "";
    }
    
    // Přečtěte výstup z potrubí
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Zkontrolujte, zda příkaz úspěšně skončil
    int status = pclose(pipe.release());
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        return "";
    }
    
    // Obnovte ukazatel, protože jsme ho uvolnili výše
    pipe.reset(nullptr);
    
    return result;
}