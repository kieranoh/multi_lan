#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Longitud de clave RSA estándar
    
    // Construir el comando para generar la clave privada RSA
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Buffer para almacenar el resultado
    std::array<char, 128> buffer;
    std::string result;
    
    // Abrir un pipe para leer la salida del comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Error al abrir el pipe
        return "";
    }
    
    // Leer la salida del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Verificar si se generó una clave válida
    if (result.empty() || result.find("-----BEGIN PRIVATE KEY-----") == std::string::npos) {
        return "";
    }
    
    return result;
}