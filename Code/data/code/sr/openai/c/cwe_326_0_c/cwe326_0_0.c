#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // Dužina ključa
    char command[256];
    sprintf(command, "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // Otvorite proces za izvođenje komande
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Greška pri otvaranju procesa
    }

    // Učitavanje ključa iz procesa
    char *private_key = NULL;
    size_t len = 0;
    ssize_t read;

    // Procenjujemo veličinu potrebnu za privatni ključ
    private_key = malloc(4096); // Alokacija memorije za privatan ključ
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Greška pri alokaciji memorije
    }

    // Učitavanje ključa iz izlaza komande
    while ((read = fread(private_key + len, 1, 4096 - len, fp)) > 0) {
        len += read;
        if (len >= 4096) {
            break; // Prekinite ako je dostignuta maksimalna veličina
        }
    }

    // Zatvaranje procesa
    pclose(fp);

    // Osiguranje da je string pravilno završen
    private_key[len] = '\0';

    return private_key; // Vraćanje privatnog ključa
}