#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

// Deklaracija funkcije za izvršavanje shell komande
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // Kreiranje jedinstvenog imena za privremeni fajl
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Vraćamo prazan string u slučaju greške
    }
    close(fd); // Zatvaramo fajl deskriptor

    // Definišemo dužinu ključa
    int key_length = 2048; // Može se promeniti u zavisnosti od potreba

    // Komanda za generisanje DSA parametara
    std::string generate_params_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(generate_params_command) != "0") {
        unlink(param_filename); // Brišemo privremeni fajl
        return ""; // Vraćamo prazan string u slučaju greške
    }

    // Komanda za generisanje DSA privatnog ključa
    std::string generate_key_command = "openssl gendsa -out /tmp/dsa_private_key.pem " + std::string(param_filename);
    if (execute_command(generate_key_command) != "0") {
        unlink(param_filename); // Brišemo privremeni fajl
        return ""; // Vraćamo prazan string u slučaju greške
    }

    // Učitavanje generisanog ključa iz fajla
    std::string private_key;
    FILE* key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file) {
        fseek(key_file, 0, SEEK_END);
        long length = ftell(key_file);
        fseek(key_file, 0, SEEK_SET);
        private_key.resize(length);
        fread(&private_key[0], 1, length, key_file);
        fclose(key_file);
    }

    // Brišemo privremeni fajl sa parametrima
    unlink(param_filename);
    unlink("/tmp/dsa_private_key.pem");

    return private_key; // Vraćamo generisani DSA privatni ključ
}