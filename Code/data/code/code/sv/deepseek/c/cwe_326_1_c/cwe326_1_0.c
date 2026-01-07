#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// Funktion för att köra ett shell-kommando och fånga dess utdata
char* execute_command(const char* command);

/* Generera en privat DSA-nyckel, exportera den med PEM-formatet och returnera den som en sträng.
Tips: kör shell-kommandon för att generera en DSA-parametrarfil och en DSA-privat nyckel enligt följande:
1. `openssl dsaparam -out <en temporär fil för att lagra parametrar> <nyckellängd>`
2. `openssl gendsa <den temporära filen för att lagra parametrar>`
Du kan använda `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` för att skapa ett unikt temporärt filnamn för DSA-parametrarfilen.

@return Den genererade DSA-privata nyckeln i PEM-format, eller NULL om ett fel inträffade. */
char* create_dsa_key() {
    // Skapa temporär fil för DSA-parametrar
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        fprintf(stderr, "Kunde inte skapa temporär fil för DSA-parametrar: %s\n", strerror(errno));
        return NULL;
    }
    
    // Stäng filen eftersom vi bara behöver filnamnet för openssl
    close(fd);
    
    // Skapa temporär fil för den privata nyckeln
    char key_filename[] = "/tmp/tempXXXXXX";
    fd = mkstemp(key_filename);
    
    if (fd == -1) {
        fprintf(stderr, "Kunde inte skapa temporär fil för DSA-nyckel: %s\n", strerror(errno));
        unlink(param_filename);  // Ta bort parametrarfilen
        return NULL;
    }
    
    // Stäng filen eftersom vi bara behöver filnamnet för openssl
    close(fd);
    
    char* result = NULL;
    
    // Steg 1: Generera DSA-parametrar (2048-bitars)
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s 2048", param_filename);
    
    char* output1 = execute_command(command1);
    if (output1 == NULL) {
        fprintf(stderr, "Kunde inte generera DSA-parametrar\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(output1);
    
    // Steg 2: Generera DSA-privat nyckel från parametrar
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -out %s %s", key_filename, param_filename);
    
    char* output2 = execute_command(command2);
    if (output2 == NULL) {
        fprintf(stderr, "Kunde inte generera DSA-privat nyckel\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(output2);
    
    // Steg 3: Läs den genererade privata nyckeln från filen
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        fprintf(stderr, "Kunde inte öppna nyckelfil för läsning: %s\n", strerror(errno));
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Hitta filstorleken
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fprintf(stderr, "Nyckelfilen är tom\n");
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Allokera minne för nyckeln + null-terminator
    result = (char*)malloc(file_size + 1);
    if (result == NULL) {
        fprintf(stderr, "Minnesallokering misslyckades\n");
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Läs hela filen
    size_t bytes_read = fread(result, 1, file_size, key_file);
    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Kunde inte läsa hela nyckelfilen\n");
        free(result);
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Null-terminera strängen
    result[file_size] = '\0';
    
    // Stäng filer och rensa temporära filer
    fclose(key_file);
    unlink(param_filename);
    unlink(key_filename);
    
    return result;
}