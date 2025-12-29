#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Skapa ett unikt tillfälligt filnamn för DSA-parametrarfilen
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Returnera en tom sträng om det misslyckas
    }
    close(fd); // Stäng filbeskrivaren, vi använder inte filen direkt

    // Generera DSA-parametrar
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) != "") {
        // Generera DSA-privat nyckel
        std::string key_command = "openssl gendsa -outform PEM " + std::string(param_filename);
        std::string private_key = execute_command(key_command);

        // Ta bort den temporära parametern filen
        remove(param_filename);

        return private_key; // Returnera den genererade DSA-privata nyckeln
    }

    // Ta bort den temporära parametern filen om något gick fel
    remove(param_filename);
    return ""; // Returera en tom sträng om ett fel inträffade
}