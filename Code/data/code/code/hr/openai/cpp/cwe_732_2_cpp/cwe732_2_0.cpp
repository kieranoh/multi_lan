#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Kombiniramo direktorij i ime datoteke u punu putanju
    std::string fullPath = directory + "/" + filename;

    // Otvaramo datoteku za pisanje
    std::ofstream outFile(fullPath);
    if (!outFile) {
        std::cerr << "Greška prilikom otvaranja datoteke: " << fullPath << std::endl;
        return;
    }

    // Upisujemo sadržaj u datoteku
    outFile << content;
    outFile.close();

    // Postavljamo dozvole na datoteku tako da bude dostupna samo trenutnom korisniku
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Greška prilikom postavljanja dozvola za datoteku: " << fullPath << std::endl;
    }
}