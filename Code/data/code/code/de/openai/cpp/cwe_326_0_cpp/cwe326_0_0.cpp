#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // Schlüsselgröße in Bits
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Einmaligen Speicher für das Ergebnis allozieren
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // Fehler beim Öffnen der Pipe
    }

    // Lesen des Outputs der Pipe
    std::string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer; // Ergebnis anhängen
    }

    return result.empty() ? nullptr : result; // Rückgabe des Ergebnisses oder NULL bei Fehler
}