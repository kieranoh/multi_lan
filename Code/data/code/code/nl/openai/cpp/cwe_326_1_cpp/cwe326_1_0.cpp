#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

// Functie om een shell-opdracht uit te voeren en de uitvoer vast te leggen; de aanroeper is verantwoordelijk voor het vrijgeven van het geheugen.
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Sleutel lengte die we willen gebruiken voor DSA
    const int key_length = 2048;

    // Maak een tijdelijke bestandsnaam aan voor de DSA-parameterfile
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Fout bij het maken van een tijdelijk bestand
    }
    close(fd); // Sluit het bestandshandle, we gebruiken het alleen voor opslag.

    // Opdracht om DSA-parameters te genereren
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) != "") {
        return ""; // Fout bij het genereren van DSA-parameters
    }

    // Opdracht om de DSA-privesleutel te genereren
    std::string key_command = "openssl gendsa -outform PEM " + std::string(param_filename);
    std::string private_key = execute_command(key_command);
    
    // Verwijder het tijdelijke bestand
    unlink(param_filename);

    // Retourneer de DSA-privesleutel in PEM-formaat of een lege string bij een fout
    return private_key.empty() ? "" : private_key;
}