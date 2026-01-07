#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Skapa en buffer för att fånga resultatet från kommandot
    char *output = NULL;
    size_t size = 0;
    FILE *fp;

    // Skapa kommandosträngen
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s 2>&1", dir_path);

    // Öppna en process för att köra kommandot
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Returnera en tom sträng vid fel
    }

    // Läs kommandots utdata
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_output = realloc(output, size + len + 1);
        if (new_output == NULL) {
            free(output); // Frigör tidigare allokerad minne vid omallokeringfel
            pclose(fp);
            return ""; // Returnera en tom sträng vid fel
        }
        output = new_output;
        strcpy(output + size, buffer);
        size += len;
    }

    // Stäng processen
    if (pclose(fp) == -1) {
        free(output); // Frigör minnet vid fel
        return ""; // Returnera en tom sträng vid fel
    }

    return output; // Returnera resultatet
}