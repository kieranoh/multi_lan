#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <memory>

// Declaratie van de gegeven hulpfunctie
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Tijdelijke bestandsnaam voor DSA-parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Fout bij aanmaken tijdelijk bestand
    }
    close(fd); // We gebruiken alleen de naam, niet de file descriptor

    // Sleutellengte voor DSA (2048 bits is gangbaar)
    const int key_length = 2048;

    // 1. Genereer DSA-parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length) + " 2>&1";
    std::string param_output = execute_command(param_command);
    
    // Controleer of het genereren van parameters is gelukt
    if (param_output.find("writing new DSA parameters") == std::string::npos) {
        std::remove(param_filename); // Opruimen
        return "";
    }

    // 2. Genereer DSA-privésleutel van de parameters
    std::string key_command = "openssl gendsa " + std::string(param_filename) + " 2>&1";
    std::string key_output = execute_command(key_command);

    // Verwijder het tijdelijke parameterbestand
    std::remove(param_filename);

    // Controleer of de sleutelgeneratie is gelukt
    if (key_output.find("Generating DSA key") == std::string::npos) {
        return "";
    }

    // 3. Exporteer de privésleutel in PEM-formaat
    std::string export_command = "openssl dsa 2>&1";
    // We gebruiken een pipe om de gegenereerde sleutel door te geven aan openssl dsa
    // Omdat execute_command een shell-opdracht uitvoert, kunnen we een pipe gebruiken
    std::string full_command = "echo \"" + key_output + "\" | openssl dsa -outform PEM 2>&1";
    std::string pem_output = execute_command(full_command);

    // Controleer of de export is gelukt (PEM-formaat begint met "-----BEGIN DSA PRIVATE KEY-----")
    if (pem_output.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
        return "";
    }

    return pem_output;
}