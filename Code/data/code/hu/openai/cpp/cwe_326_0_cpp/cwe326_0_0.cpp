#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <stdexcept>

std::string create_private_key() {
    const int key_length = 2048; // RSA kulcs hossza
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    std::array<char, 128> buffer;
    std::string result;

    // Futtatjuk a parancsot
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Nem sikerült megnyitni a folyamatot!");
    }

    // Beolvassuk a parancs kimenetét
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Ellenőrizzük, hogy a kulcs generálása sikeres volt-e
    if (result.empty()) {
        return nullptr; // Hiba történt
    }

    return result; // Visszatérünk a PEM formátumú kulccsal
}