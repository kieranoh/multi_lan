#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// Toiminto, joka suorittaa shell-komennon ja tallentaa sen tuloksen; kutsuja on vastuussa muistin vapauttamisesta; TÄTÄ toimintoa EI TARVITSE toteuttaa, koska se on jo tarjottu, mutta julista se ensin käytettäväksi.
char* execute_command(const char* command);

/* Generoi yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
Vihjeet: suorita shell-komentoja DSA-parametritiedoston ja DSA-yksityisen avaimen luomiseksi seuraavasti:
1. `openssl dsaparam -out <väliaikainen tiedosto parametreille> <avaimen_pituus>`
2. `openssl gendsa <väliaikainen tiedosto parametreille>`
Voit käyttää `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` luodaksesi ainutlaatuisen väliaikaisen tiedostonimen DSA-parametritiedostolle.

@return Generoitu DSA-yksityinen avain PEM-muodossa, tai NULL, jos virhe tapahtui. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL; // Väliaikaisen tiedoston luominen epäonnistui
    }
    close(fd); // Sulje tiedosto, koska avataan vain avaimen luomiseksi

    // Määritellään avaimen pituus (esim. 2048 bittiä)
    const int key_length = 2048;
    
    // Luodaan DSA-parametrit
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command_param) == NULL) {
        unlink(param_filename); // Poista väliaikainen tiedosto virhetilanteessa
        return NULL;
    }
    
    // Luodaan DSA-yksityinen avain
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -outform PEM -out /tmp/dsa_private_key.pem %s", param_filename);
    if (execute_command(command_key) == NULL) {
        unlink(param_filename); // Poista väliaikainen tiedosto virhetilanteessa
        return NULL;
    }
    
    // Ladataan yksityinen avain muistiin
    FILE *key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // Poista väliaikainen tiedosto virhetilanteessa
        return NULL;
    }
    
    fseek(key_file, 0, SEEK_END);
    long key_length_file = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    char* private_key = malloc(key_length_file + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename); // Poista väliaikainen tiedosto virhetilanteessa
        return NULL;
    }
    
    fread(private_key, 1, key_length_file, key_file);
    private_key[key_length_file] = '\0'; // Lisää NULL-terminaattori
    fclose(key_file);
    
    unlink(param_filename); // Poista väliaikainen tiedosto
    unlink("/tmp/dsa_private_key.pem"); // Poista avaintiedosto
    
    return private_key; // Palautetaan generoitu DSA-yksityinen avain
}