#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>

// Declaración de la función proporcionada
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Longitud de clave DSA recomendada (2048 bits)
    const int key_length = 2048;
    
    // Crear nombres de archivos temporales
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    
    // Crear archivo temporal para parámetros
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        return "";
    }
    close(param_fd);
    
    // Crear archivo temporal para clave privada
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename);
        return "";
    }
    close(key_fd);
    
    std::string result = "";
    
    try {
        // Paso 1: Generar parámetros DSA
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length);
        std::string param_output = execute_command(param_cmd);
        
        // Verificar si el comando se ejecutó correctamente
        if (param_output.empty()) {
            throw std::runtime_error("Error al generar parámetros DSA");
        }
        
        // Paso 2: Generar clave privada DSA
        std::string key_cmd = "openssl gendsa -out " + std::string(key_filename) + 
                              " " + std::string(param_filename);
        std::string key_output = execute_command(key_cmd);
        
        if (key_output.empty()) {
            throw std::runtime_error("Error al generar clave DSA");
        }
        
        // Paso 3: Leer la clave privada generada
        std::string read_cmd = "cat " + std::string(key_filename);
        result = execute_command(read_cmd);
        
        // Verificar que la clave no esté vacía
        if (result.empty() || result.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            throw std::runtime_error("Clave DSA generada inválida");
        }
        
    } catch (const std::exception& e) {
        // En caso de error, limpiar y retornar cadena vacía
        result = "";
    }
    
    // Limpiar archivos temporales
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}