#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

// Függvény, amely végrehajt egy shell parancsot és rögzíti a kimenetét; a hívónak kell felszabadítania a memóriát.
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048; // Kulcshossz
    char param_filename[] = "/tmp/tempXXXXXX"; // Ideiglenes fájl neve
    int fd = mkstemp(param_filename); // Egyedi ideiglenes fájl létrehozása

    if (fd == -1) {
        return nullptr; // Hiba történt a fájl létrehozásakor
    }
    
    // DSA paraméterek generálása
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == nullptr) {
        close(fd);
        unlink(param_filename); // Fájl törlése hiba esetén
        return nullptr;
    }
    
    // DSA privát kulcs generálása
    std::string gen_key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(gen_key_command);

    // Fájl bezárása és törlése
    close(fd);
    unlink(param_filename); // Ideiglenes fájl törlése

    if (private_key.empty()) {
        return nullptr; // Hiba történt a kulcs generálásakor
    }

    return private_key; // Visszatérés a DSA privát kulccsal PEM formátumban
}