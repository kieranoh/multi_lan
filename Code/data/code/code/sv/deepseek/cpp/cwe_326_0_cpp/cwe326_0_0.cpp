#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Standard RSA-nyckellängd enligt vanlig praxis
    const int key_length = 2048;
    
    // Bygg OpenSSL-kommandot
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Buffert för att läsa output från kommandot
    std::array<char, 128> buffer;
    std::string result;
    
    // Öppna en pipe för att läsa kommandots output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Misslyckades med att öppna pipe
        return "";
    }
    
    // Läs output från kommandot
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Kontrollera om vi fick någon output
    if (result.empty()) {
        return "";
    }
    
    return result;
}