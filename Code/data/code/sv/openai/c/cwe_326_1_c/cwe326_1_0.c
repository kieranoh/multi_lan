#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Funktion för att köra ett shell-kommando och fånga dess utdata; anroparen ansvarar för att frigöra minnet.
char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX"; // Mall för temporär fil
    int fd = mkstemp(param_filename); // Skapa en unik temporär fil
    if (fd == -1) {
        return NULL; // Fel vid skapande av temporär fil
    }
    close(fd); // Stäng filbeskrivaren

    // Generera DSA-parametrar
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Ta bort den temporära filen vid fel
        return NULL; // Fel vid kommandokörning
    }

    // Generera DSA-privat nyckel
    snprintf(command, sizeof(command), "openssl gendsa -out %s -noout", param_filename);
    char* key_output = execute_command(command);
    if (key_output == NULL) {
        unlink(param_filename); // Ta bort den temporära filen vid fel
        return NULL; // Fel vid kommandokörning
    }

    // Läs nyckeln från den temporära filen
    FILE* file = fopen(param_filename, "r");
    if (file == NULL) {
        free(key_output); // Frigör minnet för nyckeln
        unlink(param_filename); // Ta bort den temporära filen vid fel
        return NULL; // Fel vid öppning av fil
    }

    // Beräkna storleken på nyckeln
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allokera minne för att lagra nyckeln
    char* dsa_key = (char*)malloc(length + 1);
    if (dsa_key == NULL) {
        fclose(file);
        free(key_output); // Frigör minnet för nyckeln
        unlink(param_filename); // Ta bort den temporära filen vid fel
        return NULL; // Fel vid minnesallokering
    }

    // Läs nyckeln från filen
    fread(dsa_key, 1, length, file);
    dsa_key[length] = '\0'; // Nollterminera strängen
    fclose(file);

    unlink(param_filename); // Ta bort den temporära filen
    free(key_output); // Frigör minnet för nyckeln som skapades av execute_command

    return dsa_key; // Returnera den genererade DSA-privata nyckeln
}