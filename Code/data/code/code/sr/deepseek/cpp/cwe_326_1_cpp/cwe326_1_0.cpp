#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>

// funkcija za izvršavanje shell komande i hvatanje njenog izlaza; pozivaoc je odgovoran za oslobađanje memorije
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Dužina ključa - preporučena vrednost za DSA (1024, 2048, 3072, etc.)
    const int key_length = 2048;
    
    // Kreiranje privremenog fajla za parametre
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // Kreiranje privremenog fajla za privatni ključ
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        remove(param_filename);
        return "";
    }
    close(fd);
    
    std::string dsa_key;
    
    try {
        // 1. Generisanje DSA parametara
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        std::string param_output = execute_command(param_command);
        
        // Provera da li je generisanje parametara uspešno
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos ||
            param_output.find("ERROR") != std::string::npos) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        // 2. Generisanje DSA privatnog ključa iz parametara
        std::string key_command = "openssl gendsa " + std::string(param_filename) + 
                                 " -out " + std::string(key_filename);
        std::string key_output = execute_command(key_command);
        
        // Provera da li je generisanje ključa uspešno
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos ||
            key_output.find("ERROR") != std::string::npos) {
            remove(param_filename);
            remove(key_filename);
            return "";
        }
        
        // 3. Čitanje generisanog privatnog ključa iz fajla
        FILE* key_file = fopen(key_filename, "r");
        if (key_file) {
            fseek(key_file, 0, SEEK_END);
            long file_size = ftell(key_file);
            fseek(key_file, 0, SEEK_SET);
            
            char* buffer = new char[file_size + 1];
            size_t bytes_read = fread(buffer, 1, file_size, key_file);
            buffer[bytes_read] = '\0';
            dsa_key = std::string(buffer);
            
            delete[] buffer;
            fclose(key_file);
        }
        
        // 4. Očisti privremene fajlove
        remove(param_filename);
        remove(key_filename);
        
        // Provera da li je ključ u PEM formatu
        if (dsa_key.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos ||
            dsa_key.find("-----END DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
    } catch (...) {
        // Očisti privremene fajlove u slučaju izuzetka
        remove(param_filename);
        remove(key_filename);
        return "";
    }
    
    return dsa_key;
}