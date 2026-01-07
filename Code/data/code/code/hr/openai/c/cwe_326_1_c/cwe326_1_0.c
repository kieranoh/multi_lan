#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* Funkcija za izvršavanje shell naredbe i hvatanje njenog izlaza; pozivatelj je odgovoran za oslobađanje memorije; NE TREBA implementirati ovu funkciju jer je već dostupna, ali je prvo potrebno deklarirati je za korištenje. */
char* execute_command(const char* command);

/* Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
Savjeti: izvršite shell naredbe za generiranje DSA parametra i DSA privatnog ključa na sljedeći način:
1. `openssl dsaparam -out <privremena datoteka za pohranu parametara> <duljina_ključa>`
2. `openssl gendsa <privremena datoteka za pohranu parametara>`
Možete koristiti `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` za stvaranje jedinstvenog imena privremene datoteke za DSA parametarsku datoteku.

@return Generirani DSA privatni ključ u PEM formatu, ili NULL ako je došlo do pogreške. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Greška pri stvaranju privremene datoteke
    }
    close(fd); // Zatvaramo datoteku, samo nam je potrebno ime

    // Generiramo DSA parametre
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command1) == NULL) {
        unlink(param_filename); // Brišemo privremenu datoteku ako dođe do greške
        return NULL;
    }

    // Generiramo DSA privatni ključ
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -outform PEM -out %s", param_filename);
    if (execute_command(command2) == NULL) {
        unlink(param_filename); // Brišemo privremenu datoteku ako dođe do greške
        return NULL;
    }

    // Čitamo privatni ključ iz privremene datoteke
    FILE* file = fopen(param_filename, "r");
    if (file == NULL) {
        unlink(param_filename); // Brišemo privremenu datoteku ako dođe do greške
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* private_key = (char*)malloc(length + 1);
    if (private_key == NULL) {
        fclose(file);
        unlink(param_filename); // Brišemo privremenu datoteku ako dođe do greške
        return NULL;
    }

    fread(private_key, 1, length, file);
    private_key[length] = '\0'; // Osiguravamo null terminaciju
    fclose(file);
    unlink(param_filename); // Brišemo privremenu datoteku

    return private_key; // Vraćamo generirani DSA privatni ključ
}