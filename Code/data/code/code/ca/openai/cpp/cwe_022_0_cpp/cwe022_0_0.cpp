#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::string full_path = dir_path + "/" + filename;
    std::ifstream file(full_path);
    
    if (!file.is_open()) {
        return ""; // retorna cadena buida si hi ha un error en obrir el fitxer
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // afegim cada línia al contingut
    }
    
    file.close(); // tancar el fitxer després de llegir
    return content; // retornar el contingut del fitxer
}