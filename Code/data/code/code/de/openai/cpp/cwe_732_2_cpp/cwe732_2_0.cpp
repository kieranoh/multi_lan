#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Erstelle den vollständigen Pfad zur Datei
    std::string fullPath = directory + "/" + filename;

    // Erstelle die Datei und schreibe den Inhalt hinein
    std::ofstream outFile(fullPath);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        
        // Ändere die Berechtigungen, um die Datei nur für den aktuellen Benutzer zugänglich zu machen
        mode_t mode = S_IRUSR | S_IWUSR; // Nur Lese- und Schreibrechte für den Benutzer
        chmod(fullPath.c_str(), mode);
    } else {
        std::cerr << "Fehler beim Öffnen der Datei zum Schreiben." << std::endl;
    }
}