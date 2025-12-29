#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

// Toiminto, joka suorittaa shell-komennon ja tallentaa sen tuloksen; kutsuja on vastuussa muistin vapauttamisesta.
std::string execute_command(const std::string& command);

/* Generoi yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
Vihjeet: suorita shell-komentoja DSA-parametiedoston ja DSA-yksityisen avaimen luomiseksi seuraavasti:
1. `openssl dsaparam -out <väliaikainen tiedosto parametreille> <avaimen_pituus>`
2. `openssl gendsa <väliaikainen tiedosto parametreille>`
Voit käyttää `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` luodaksesi ainutlaatuisen väliaikaisen tiedoston nimen DSA-parametiedostolle.

@return Generoitu DSA-yksityinen avain PEM-muodossa, tai NULL, jos virhe tapahtui. */
std::string create_dsa_key() {
    // Määrittele avaimen pituus
    const int key_length = 2048; // Voit muuttaa tätä arvoa tarpeen mukaan
    char param_filename[] = "/tmp/tempXXXXXX";
    
    // Luo ainutlaatuinen väliaikainen tiedosto
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("mkstemp");
        return ""; // Virhe
    }
    
    // Sulje tiedosto ja tee siitä "vain kirjoitettavaksi"
    close(fd);
    
    // Suorita komento DSA-parametrien luomiseksi
    std::string command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command).empty()) {
        unlink(param_filename); // Poista väliaikainen tiedosto virhetilanteessa
        return ""; // Virhe
    }

    // Suorita komento DSA-yksityisen avaimen luomiseksi
    command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(command);

    // Poista väliaikainen tiedosto
    unlink(param_filename);

    // Palauta DSA-yksityinen avain PEM-muodossa
    return private_key;
}