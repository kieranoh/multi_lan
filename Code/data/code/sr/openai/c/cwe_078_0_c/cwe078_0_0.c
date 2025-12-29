#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *result = NULL;
    size_t total_length = 0;

    // Formiranje komande
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Otvoriti proces za izvođenje komande
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Greška prilikom otvaranja procesa
    }

    // Čitanje izlaza komande
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t buffer_length = strlen(buffer);
        char *new_result = realloc(result, total_length + buffer_length + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // Greška pri alokaciji memorije
        }
        result = new_result;
        strcpy(result + total_length, buffer);
        total_length += buffer_length;
    }

    // Zatvaranje procesa
    if (pclose(fp) == -1) {
        free(result);
        return ""; // Greška prilikom zatvaranja procesa
    }

    return result; // Vraća rezultat
}