#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Longitud de clau predeterminada
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                          std::to_string(key_length) + " 2>/dev/null";
    
    // Utilitzem un array per emmagatzemar la sortida de la comanda
    std::array<char, 128> buffer;
    std::string result;
    
    // Obrim un pipe per llegir la sortida de la comanda
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Error en obrir el pipe
        return "";
    }
    
    // Llegim la sortida de la comanda
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Comprovem si s'ha generat alguna clau
    if (result.empty()) {
        return "";
    }
    
    return result;
}