#include <fstream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <sys/stat.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Crear el directori si no existeix
    std::filesystem::create_directories(directory);
    
    // Crear la ruta completa del fitxer
    std::string filePath = directory + "/" + filename;
    
    // Desar el contingut al fitxer
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << content;
        outFile.close();
        
        // Ajustar els permisos del fitxer perquè només l'usuari actual pugui accedir-hi
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        throw std::runtime_error("No s'ha pogut obrir el fitxer per escriure.");
    }
}