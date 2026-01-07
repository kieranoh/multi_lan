#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const std::string key_length = "2048"; // Puedes cambiar la longitud de la clave aquí
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + key_length + " 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // Execute the command and read the output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Retorna cadena vacia en cas d'error
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result.empty() ? "" : result; // Retorna la clau privada o cadena buida en cas d'error
}