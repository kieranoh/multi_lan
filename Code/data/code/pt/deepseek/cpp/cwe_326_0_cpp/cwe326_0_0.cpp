#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Tamanho da chave RSA (em bits)
    const int key_length = 2048;
    
    // Comando para gerar a chave RSA privada
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Buffer para armazenar a saída do comando
    std::array<char, 128> buffer;
    std::string result;
    
    // Abre um pipe para executar o comando e capturar sua saída
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Falha ao abrir o pipe
        return "";
    }
    
    // Lê a saída do comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Verifica se a chave foi gerada com sucesso
    if (result.empty() || result.find("-----BEGIN PRIVATE KEY-----") == std::string::npos) {
        return "";
    }
    
    return result;
}