#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Fitxategiaren bidea osatu
    std::string filePath = directory + "/" + filename;

    // Fitxategia sortu eta idatzi
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
    } else {
        std::cerr << "Ez da fitxategia sortu: " << filePath << std::endl;
        return;
    }

    // Fitxategiaren baimenen ezarpena (egungo erabiltzailearentzat bakarrik)
    mode_t newMode = S_IRUSR | S_IWUSR; // Irakurri eta idatzi baimenak egungo erabiltzailearentzat
    if (chmod(filePath.c_str(), newMode) != 0) {
        std::cerr << "Ez da baimenak aldatzea lortu: " << filePath << std::endl;
    }
}