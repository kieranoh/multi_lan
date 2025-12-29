#include <fstream>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <sys/stat.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Verificar si el directorio existe
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        throw std::invalid_argument("El directorio especificado no existe o no es un directorio.");
    }

    // Crear la ruta completa del archivo
    std::string filePath = directory + "/" + filename;

    // Guardar el contenido en el archivo
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("No se pudo abrir el archivo para escribir.");
    }
    outFile << content;
    outFile.close();

    // Cambiar las permisos del archivo para que solo el usuario actual pueda acceder a él
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("No se pudo cambiar los permisos del archivo.");
    }
}