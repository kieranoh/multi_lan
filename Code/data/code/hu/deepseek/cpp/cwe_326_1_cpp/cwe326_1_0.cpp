#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>
#include <fstream>
#include <sstream>

// függvény, amely végrehajt egy shell parancsot és rögzíti a kimenetét; a hívónak kell felszabadítania a memóriát; NEM szükséges ezt a függvényt megvalósítani, mivel később biztosítva van (de itt deklaráld, hogy használni tudd).
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_size = 2048; // DSA kulcs hossza
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    
    // Ideiglenes fájlok létrehozása a paramétereknek és a kulcsnak
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        return "";
    }
    close(param_fd);
    
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename);
        return "";
    }
    close(key_fd);
    
    std::string result;
    
    try {
        // 1. DSA paraméterek generálása
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_size) + " 2>&1";
        
        std::string param_output = execute_command(param_command);
        
        // Ellenőrizzük, hogy sikeres volt-e a paraméter generálás
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos ||
            param_output.find("ERROR") != std::string::npos) {
            throw std::runtime_error("DSA paraméter generálás sikertelen");
        }
        
        // 2. DSA privát kulcs generálása a paraméterekből
        std::string key_command = "openssl gendsa " + std::string(param_filename) + 
                                 " -out " + std::string(key_filename) + " 2>&1";
        
        std::string key_output = execute_command(key_command);
        
        // Ellenőrizzük, hogy sikeres volt-e a kulcs generálás
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos ||
            key_output.find("ERROR") != std::string::npos) {
            throw std::runtime_error("DSA kulcs generálás sikertelen");
        }
        
        // 3. Olvassuk be a generált kulcsot
        std::ifstream key_file(key_filename);
        if (!key_file.is_open()) {
            throw std::runtime_error("Nem sikerült megnyitni a kulcs fájlt");
        }
        
        std::stringstream key_stream;
        key_stream << key_file.rdbuf();
        result = key_stream.str();
        
        key_file.close();
        
        // Ellenőrizzük, hogy a kulcs nem üres
        if (result.empty()) {
            throw std::runtime_error("A generált kulcs üres");
        }
        
        // Ellenőrizzük, hogy PEM formátumú-e
        if (result.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            throw std::runtime_error("A generált kulcs nem PEM formátumú");
        }
        
    } catch (const std::exception& e) {
        result = "";
    }
    
    // Ideiglenes fájlok törlése
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}