#include <string>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Direktorioaren bidea eta fitxategiaren bidea osatu
    std::filesystem::path dirPath(directory);
    std::filesystem::path filePath = dirPath / filename;
    
    // Direktorioa existitzen ez bada, sortu
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }
    
    // Fitxategia idazteko ireki
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Ezin izan da fitxategia ireki idazteko: " + filePath.string());
    }
    
    // Edukia idatzi
    outFile.write(content.data(), content.size());
    outFile.close();
    
    // Baimenak ezarri: erabiltzailearentzat bakarrik irakurri/idatzi (600)
    chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
}