#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    // Comando da eseguire
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Apertura di un processo per eseguire il comando
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Errore nell'aprire il processo
    }

    // Buffer per memorizzare l'output
    char *output = malloc(BUFFER_SIZE);
    if (output == NULL) {
        pclose(fp);
        return ""; // Errore nell'allocazione della memoria
    }
    
    // Leggi l'output dal comando
    size_t total_length = 0;
    size_t bytes_read;
    while ((bytes_read = fread(output + total_length, 1, BUFFER_SIZE - total_length, fp)) > 0) {
        total_length += bytes_read;
        if (total_length >= BUFFER_SIZE - 1) {
            // Se il buffer è pieno, ri-alloca più memoria
            char *new_output = realloc(output, total_length + BUFFER_SIZE);
            if (new_output == NULL) {
                free(output);
                pclose(fp);
                return ""; // Errore nell'allocazione della memoria
            }
            output = new_output;
        }
    }

    // Assicurati che l'output sia null-terminato
    output[total_length] = '\0';

    // Chiudi il processo
    pclose(fp);
    
    // Restituisci l'output
    return output;
}