#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

// Funció per executar una comanda de shell i capturar la seva sortida
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Crear un nom de fitxer temporal únic per als paràmetres DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);  // Tancar el descriptor de fitxer, només necessitem el nom

    // Crear un nom de fitxer temporal únic per a la clau privada DSA
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    if (fd == -1) {
        unlink(param_filename);  // Netejar el fitxer de paràmetres
        return "";
    }
    close(fd);  // Tancar el descriptor de fitxer, només necessitem el nom

    // Longitud de la clau DSA (2048 bits és una mida segura)
    const int key_length = 2048;

    // Generar els paràmetres DSA
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length);
    std::string param_output = execute_command(param_command);
    
    // Verificar si la generació de paràmetres ha fallat
    if (param_output.find("error") != std::string::npos || 
        param_output.find("Error") != std::string::npos ||
        param_output.find("ERROR") != std::string::npos) {
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }

    // Generar la clau privada DSA
    std::string key_command = "openssl gendsa " + std::string(param_filename) + 
                              " -out " + std::string(key_filename);
    std::string key_output = execute_command(key_command);
    
    // Verificar si la generació de la clau ha fallat
    if (key_output.find("error") != std::string::npos || 
        key_output.find("Error") != std::string::npos ||
        key_output.find("ERROR") != std::string::npos) {
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }

    // Llegir la clau privada del fitxer
    FILE* key_file = fopen(key_filename, "r");
    if (!key_file) {
        unlink(param_filename);
        unlink(key_filename);
        return "";
    }

    // Obtenir la mida del fitxer
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    // Llegir el contingut del fitxer
    std::string private_key;
    private_key.resize(file_size);
    size_t bytes_read = fread(&private_key[0], 1, file_size, key_file);
    fclose(key_file);

    // Netejar els fitxers temporals
    unlink(param_filename);
    unlink(key_filename);

    // Verificar si s'ha llegit correctament
    if (bytes_read != static_cast<size_t>(file_size)) {
        return "";
    }

    return private_key;
}