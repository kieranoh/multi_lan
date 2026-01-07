#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <stdexcept>

std::string create_private_key() {
    const int key_length = 2048; // Możesz zmienić długość klucza, jeśli chcesz
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    std::array<char, 128> buffer;
    std::string result;
    
    // Wykonaj polecenie systemowe
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Nie można otworzyć potoku");
    }
    
    // Odczytaj dane wyjściowe z potoku
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Sprawdź, czy klucz został wygenerowany
    if (result.empty()) {
        return nullptr; // Błąd, nie wygenerowano klucza
    }
    
    return result; // Zwróć wygenerowany klucz w formacie PEM
}