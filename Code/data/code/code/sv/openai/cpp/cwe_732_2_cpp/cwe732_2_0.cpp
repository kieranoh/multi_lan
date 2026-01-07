#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Skapa den fullständiga sökvägen till den hemliga filen
    std::string filePath = directory + "/" + filename;

    // Öppna filen för att skriva
    std::ofstream outFile(filePath);

    // Kontrollera om filen kunde öppnas
    if (!outFile) {
        std::cerr << "Kunde inte öppna filen: " << filePath << std::endl;
        return;
    }

    // Skriv innehållet till filen
    outFile << content;

    // Stäng filen
    outFile.close();

    // Sätt filens rättigheter så att den endast är tillgänglig för den nuvarande användaren
    chmod(filePath.c_str(), S_IRUSR | S_IWUSR);

    std::cout << "Hemlig fil sparad som: " << filePath << std::endl;
}