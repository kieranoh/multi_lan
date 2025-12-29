#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // Tarkista, onko hakemisto olemassa ja onko se luettavissa
    std::error_code ec;
    if (!std::filesystem::exists(dir_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_directory(dir_path, ec) || ec) {
        return "";
    }
    
    // Tarkista, onko hakemistoon lukuoikeus
    std::filesystem::file_status status = std::filesystem::status(dir_path, ec);
    if (ec || (status.permissions() & std::filesystem::perms::owner_read) == std::filesystem::perms::none) {
        return "";
    }
    
    // Muodosta komento
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Suorita komento ja lue stdout
    std::array<char, 128> buffer;
    std::string result;
    
    // Avaa putki komennon suorittamiseen
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    
    // Lue komentotuloste
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Tarkista, että komento suoritettiin onnistuneesti
    int exit_status = pclose(pipe.release());
    if (exit_status != 0) {
        return "";
    }
    
    // Poista mahdollinen viimeinen rivinvaihto
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}