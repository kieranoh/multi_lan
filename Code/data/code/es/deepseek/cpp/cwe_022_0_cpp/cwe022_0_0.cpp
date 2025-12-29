#include <string>
#include <fstream>
#include <filesystem>
#include <system_error>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    try {
        // Construir la ruta completa del archivo
        std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
        
        // Verificar que la ruta sea un archivo regular y accesible
        if (!std::filesystem::exists(file_path)) {
            return "";
        }
        
        if (!std::filesystem::is_regular_file(file_path)) {
            return "";
        }
        
        // Abrir el archivo en modo binario para leer todo tipo de contenido
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            return "";
        }
        
        // Leer el contenido completo del archivo
        std::string content;
        file.seekg(0, std::ios::end);
        content.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&content[0], content.size());
        
        // Verificar si hubo errores durante la lectura
        if (!file) {
            return "";
        }
        
        return content;
    }
    catch (const std::filesystem::filesystem_error&) {
        // Capturar errores del sistema de archivos (permisos, etc.)
        return "";
    }
    catch (const std::bad_alloc&) {
        // Capturar errores de asignación de memoria
        return "";
    }
    catch (...) {
        // Capturar cualquier otro error inesperado
        return "";
    }
}