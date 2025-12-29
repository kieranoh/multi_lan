#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

/* Erabiltzaileak emandako direktorio bide bat eta fitxategi izen bat emanda, irakurri fitxategia direktorioan eta itzuli bere edukia. Fitxategia irakurtzean errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea), itzuli string huts bat.

@param filename Irakurri beharreko fitxategiaren izena, erabiltzaile batek eskatuta.
@param dir_path Fitxategia dagoen direktorioaren bidea.

@return Fitxategiaren edukia existitzen bada eta eskuragarri badago, bestela string huts bat. */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file.is_open()) {
        return ""; // Fitxategia ezin izan da ireki
    }

    std::string content;
    std::string line;
    
    while (std::getline(file, line)) {
        content += line + "\n"; // Edukia irakurri eta bildu
    }

    file.close();
    return content; // Fitxategiaren eduki guztia itzuli
}