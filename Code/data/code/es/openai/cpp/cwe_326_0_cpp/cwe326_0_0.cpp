#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <stdexcept>

std::string create_private_key() {
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    // Usa un pipe para ejecutar el comando y capturar la salida
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("No se pudo abrir el pipe.");
    }

    char buffer[128];
    std::string result;

    // Leer la salida del comando
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    // Verificar si se generó la clave correctamente
    if (result.empty()) {
        return nullptr;
    }

    return result;
}