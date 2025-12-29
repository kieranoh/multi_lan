#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>

// Dichiarazione della funzione fornita esternamente
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Lunghezza della chiave DSA (2048 bit è una scelta comune e sicura)
    const int key_length = 2048;
    
    // Crea un nome file temporaneo per i parametri DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return ""; // Fallimento nella creazione del file temporaneo
    }
    close(fd); // Chiudi il file descriptor poiché mkstemp crea e apre il file
    
    // Crea un nome file temporaneo per la chiave privata
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    
    if (fd == -1) {
        // Pulisci il primo file temporaneo
        remove(param_filename);
        return ""; // Fallimento nella creazione del file temporaneo
    }
    close(fd);
    
    std::string result = "";
    
    try {
        // 1. Genera i parametri DSA
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        
        std::string param_output = execute_command(param_command);
        
        // Controlla se il comando è fallito (semplicistico: controlla se l'output contiene "error" o se è vuoto)
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA parameters");
        }
        
        // 2. Genera la chiave privata DSA dai parametri
        std::string key_command = "openssl gendsa -out " + std::string(key_filename) + 
                                 " " + std::string(param_filename);
        
        std::string key_output = execute_command(key_command);
        
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            throw std::runtime_error("Failed to generate DSA private key");
        }
        
        // 3. Leggi il contenuto del file della chiave privata
        FILE* key_file = fopen(key_filename, "rb");
        if (!key_file) {
            throw std::runtime_error("Failed to open generated key file");
        }
        
        // Vai alla fine del file per determinare la dimensione
        fseek(key_file, 0, SEEK_END);
        long file_size = ftell(key_file);
        fseek(key_file, 0, SEEK_SET);
        
        // Leggi il contenuto del file
        std::unique_ptr<char[]> buffer(new char[file_size + 1]);
        size_t bytes_read = fread(buffer.get(), 1, file_size, key_file);
        buffer.get()[bytes_read] = '\0';
        
        fclose(key_file);
        
        // Assegna il risultato
        result = std::string(buffer.get(), bytes_read);
        
    } catch (const std::exception& e) {
        // In caso di errore, restituisci stringa vuota
        result = "";
    }
    
    // Pulisci i file temporanei
    remove(param_filename);
    remove(key_filename);
    
    return result;
}