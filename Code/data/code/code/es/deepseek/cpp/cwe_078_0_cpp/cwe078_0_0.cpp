#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstring>

std::string get_ls_result(const std::string &dir_path) {
    // Construir el comando con la ruta del directorio
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Buffer para almacenar la salida
    std::array<char, 128> buffer;
    std::string result;
    
    // Abrir el proceso para leer la salida
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Error al abrir el pipe
        return "";
    }
    
    // Leer la salida del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Verificar si el comando se ejecutó correctamente
    // Si result está vacío, podría ser un directorio vacío o un error
    // Para distinguir, verificamos el código de salida del comando
    int exit_code = pclose(pipe.release());
    
    // Si hubo un error (código de salida distinto de 0), devolver cadena vacía
    if (exit_code != 0) {
        return "";
    }
    
    return result;
}