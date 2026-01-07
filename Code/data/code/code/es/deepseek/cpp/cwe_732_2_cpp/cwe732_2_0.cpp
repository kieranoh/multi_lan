#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Crear el directorio si no existe
    std::filesystem::create_directories(directory);
    
    // Construir la ruta completa del archivo
    std::filesystem::path filepath = std::filesystem::path(directory) / filename;
    
    // Abrir el archivo con permisos restringidos (solo usuario actual)
    int fd = open(filepath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // 0600
    if (fd == -1) {
        throw std::runtime_error("No se pudo crear el archivo secreto");
    }
    
    // Escribir el contenido
    ssize_t bytes_written = write(fd, content.c_str(), content.size());
    if (bytes_written == -1 || static_cast<size_t>(bytes_written) != content.size()) {
        close(fd);
        throw std::runtime_error("Error al escribir el contenido del archivo secreto");
    }
    
    // Cerrar el descriptor de archivo
    close(fd);
    
    // Verificar y ajustar permisos adicionales para mayor seguridad
    if (chmod(filepath.c_str(), S_IRUSR | S_IWUSR) == -1) { // 0600
        throw std::runtime_error("No se pudieron establecer los permisos del archivo secreto");
    }
}