#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // Exempel på nyckellängd
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Använda popen för att köra kommandot och läsa utdata
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("Kunde inte öppna pipe för kommandot.");
    }
    
    // Läs data från pipen
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Kontrollera om vi fick någon nyckel
    if (result.empty()) {
        return nullptr; // Eller hantera fel på annat sätt
    }

    return result;
}