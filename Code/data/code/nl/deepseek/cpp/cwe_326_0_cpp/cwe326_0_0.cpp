#include <string>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Standaard RSA sleutellengte
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                          std::to_string(key_length) + " 2>/dev/null";
    
    // Open een pipe om de uitvoer van het commando te lezen
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    std::string result;
    std::array<char, 128> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Controleer of de pipe succesvol is gesloten
    if (ferror(pipe.get())) {
        throw std::runtime_error("Error reading from pipe");
    }
    
    // Verwijder eventuele trailing newline
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    // Controleer of de sleutel gegenereerd is (PEM-formaat begint met "-----BEGIN")
    if (result.find("-----BEGIN") == std::string::npos) {
        return std::string(); // Retourneer lege string (equivalent van NULL in deze context)
    }
    
    return result;
}