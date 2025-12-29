#include <string>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <array>
#include <sstream>

std::string create_private_key() {
    // Ustawienie długości klucza RSA (standardowo 2048 bitów)
    const int key_length = 2048;
    
    // Przygotowanie polecenia do wykonania
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // Otwarcie potoku do odczytu wyniku polecenia
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return std::string(); // Zwróć pusty string w przypadku błędu
    }
    
    // Odczytanie wyniku z potoku
    std::array<char, 128> buffer;
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Sprawdzenie czy wynik jest poprawnym kluczem PEM
    if (result.empty() || result.find("-----BEGIN PRIVATE KEY-----") == std::string::npos) {
        return std::string(); // Zwróć pusty string w przypadku błędu
    }
    
    return result;
}