#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Yhdistetään hakemistopolku ja tiedostonimi
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    try {
        // Tarkistetaan, että tiedosto on olemassa ja se on tavallinen tiedosto
        if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Tarkistetaan, että meillä on lukuoikeudet tiedostoon
        std::error_code ec;
        auto perms = std::filesystem::status(file_path, ec).permissions();
        
        if (ec || (perms & std::filesystem::perms::owner_read) == std::filesystem::perms::none) {
            return "";
        }
        
        // Avataan tiedosto binääritilassa
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        
        if (!file.is_open()) {
            return "";
        }
        
        // Haetaan tiedoston koko
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // Luetaan tiedoston sisältö
        std::string content;
        content.resize(size);
        
        if (!file.read(&content[0], size)) {
            return "";
        }
        
        return content;
        
    } catch (const std::filesystem::filesystem_error&) {
        return "";
    } catch (const std::bad_alloc&) {
        return "";
    } catch (...) {
        return "";
    }
}