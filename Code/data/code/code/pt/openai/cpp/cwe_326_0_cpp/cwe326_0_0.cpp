#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>

std::string create_private_key() {
    const int key_length = 2048; // Tamanho da chave RSA
    std::array<char, 128> buffer;
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Cria um pipe para o comando
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Falha ao abrir o pipe.");
    }

    std::stringstream result;
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result << buffer.data();
    }

    return result.str();
}