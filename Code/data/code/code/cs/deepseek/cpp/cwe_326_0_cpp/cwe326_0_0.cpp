#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // Nastavení délky klíče (typicky 2048 nebo 4096 bitů)
    const int key_length = 2048;
    
    // Sestavení příkazu pro OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Vytvoření bufferu pro čtení výstupu
    std::array<char, 128> buffer;
    std::string result;
    
    // Otevření procesu pro čtení výstupu
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Chyba při otevírání procesu
        return std::string();
    }
    
    // Čtení výstupu z příkazu
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Kontrola, zda byl klíč úspěšně vygenerován
    if (result.empty() || result.find("-----BEGIN PRIVATE KEY-----") == std::string::npos) {
        return std::string();
    }
    
    return result;
}