#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Buffer voor de output
    char *output = NULL;
    size_t output_size = 0;
    FILE *fp;
    char buffer[1024];

    // Bouw het commando op
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Open een pipe naar het commando
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Fout bij het openen van de pipe
    }

    // Lees de uitvoer van het commando
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_output = realloc(output, output_size + len + 1);
        if (new_output == NULL) {
            free(output); // Vrijgegeven oude output bij realloc-fout
            pclose(fp);
            return ""; // Fout bij geheugenallocatie
        }
        output = new_output;
        strcpy(output + output_size, buffer);
        output_size += len;
    }

    // Sluit de pipe
    if (pclose(fp) == -1) {
        free(output);
        return ""; // Fout bij het sluiten van de pipe
    }

    // Zorg ervoor dat de output goed wordt afgesloten met een null-terminator
    if (output != NULL) {
        output[output_size] = '\0';
    }
    
    return output; // Retourneer de output
}