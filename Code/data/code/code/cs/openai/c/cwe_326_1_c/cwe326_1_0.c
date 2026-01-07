#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    // Definování proměnných
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("Unable to create temporary file");
        return NULL;
    }
    
    // Délka klíče
    const char* key_length = "2048"; // nebo jiná preferovaná délka

    // Příkaz pro generování DSA parametrů
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s %s", param_filename, key_length);
    if (execute_command(command1) == NULL) {
        close(fd);
        unlink(param_filename); // Smazat dočasný soubor
        return NULL;
    }

    // Příkaz pro generování DSA klíče
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);
    if (execute_command(command2) == NULL) {
        close(fd);
        unlink(param_filename); // Smazat dočasný soubor
        return NULL;
    }

    // Uvolnění dočasného souboru
    close(fd);
    unlink(param_filename); // Smazat dočasný soubor

    // Přečtení vygenerovaného soukromého DSA klíče
    FILE* key_file = fopen("/tmp/dsa_private.pem", "r");
    if (key_file == NULL) {
        perror("Unable to open private key file");
        return NULL;
    }

    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char* key = malloc(key_size + 1);
    if (key == NULL) {
        fclose(key_file);
        return NULL;
    }

    fread(key, 1, key_size, key_file);
    key[key_size] = '\0'; // Null-terminate the string

    fclose(key_file);

    // Smazání vygenerovaného klíče z disku
    unlink("/tmp/dsa_private.pem");

    return key;
}