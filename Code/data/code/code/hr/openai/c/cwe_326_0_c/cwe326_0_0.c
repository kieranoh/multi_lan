#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // Postavka duljine ključa
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp;
    char *private_key = NULL;
    size_t key_size = 0;

    // Otvorite proces za izvođenje OpenSSL naredbe
    if ((fp = popen(command, "r")) == NULL) {
        return NULL; // Vraća NULL ako otvaranje procesa ne uspije
    }

    // Učitavanje generiranog ključa iz procesa
    fseek(fp, 0, SEEK_END);
    key_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    private_key = malloc(key_size + 1); // Alokacija memorije za ključ
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Vraća NULL ako ne uspije alokacija memorije
    }

    fread(private_key, 1, key_size, fp); // Čitajte ključeve u alociranu memoriju
    private_key[key_size] = '\0'; // Dodajte null terminator

    // Zatvorite proces
    pclose(fp);
    
    return private_key; // Vraća generirani privatni ključ
}