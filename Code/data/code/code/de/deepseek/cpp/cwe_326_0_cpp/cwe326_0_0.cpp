#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdlib>
#include <cstring>

std::string create_private_key() {
    const int key_length = 2048; // Standard RSA-Schlüssellänge
    
    // Befehl zum Generieren des privaten RSA-Schlüssels
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Puffer für die Ausgabe des Befehls
    std::array<char, 128> buffer;
    std::string result;
    
    // Öffne einen Pipe zum Lesen der Ausgabe des Befehls
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Fehler beim Öffnen des Pipes
        return std::string(); // Rückgabe eines leeren Strings (entspricht NULL im Kontext)
    }
    
    // Lese die Ausgabe des Befehls
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Überprüfe, ob die Ausgabe gültig ist (PEM-Format beginnt normalerweise mit "-----BEGIN")
    if (result.empty() || result.find("-----BEGIN") == std::string::npos) {
        return std::string(); // Rückgabe eines leeren Strings bei Fehler
    }
    
    return result;
}