#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename; // Erstellen des vollständigen Dateipfads
    std::ifstream file(full_path); // Öffnen der Datei

    if (!file.is_open()) { // Überprüfen, ob die Datei erfolgreich geöffnet wurde
        return ""; // Rückgabe eines leeren Strings bei Fehler
    }

    std::ostringstream buffer; // Puffer zum Speichern des Dateiinhalts
    buffer << file.rdbuf(); // Lesen des Dateiinhalts in den Puffer
    return buffer.str(); // Rückgabe des Inhalts als String
}