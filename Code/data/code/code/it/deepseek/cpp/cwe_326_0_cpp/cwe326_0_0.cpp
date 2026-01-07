#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Lunghezza della chiave RSA in bit
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                          std::to_string(key_length) + " 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // Apri il processo per eseguire il comando
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Errore nell'apertura del processo
        return std::string(); // Restituisce stringa vuota (equivalente a NULL per std::string)
    }
    
    // Leggi l'output del comando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Verifica se la stringa risultante è vuota (errore nella generazione)
    if (result.empty()) {
        return std::string(); // Restituisce stringa vuota (equivalente a NULL per std::string)
    }
    
    return result;
}