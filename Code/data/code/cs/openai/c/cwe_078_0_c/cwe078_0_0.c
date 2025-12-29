#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    // Alokace paměti pro výstupní řetězec
    char *output = (char *)malloc(BUFFER_SIZE);
    if (output == NULL) {
        return ""; // Vrátíme prázdný řetězec při chybě alokace
    }

    // Příkaz, který chceme spustit
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Otevření procesu pro čtení výstupu příkazu
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output);
        return ""; // Vrátíme prázdný řetězec v případě chyby
    }

    // Čtení výstupu příkazu do alokované paměti
    size_t index = 0;
    while (fgets(output + index, BUFFER_SIZE - index, fp) != NULL) {
        index += strlen(output + index);
        // Zajistíme, že nepřekročíme velikost bufferu
        if (index >= BUFFER_SIZE - 1) {
            break; // Příliš dlouhý výstup, ukončíme čtení
        }
    }

    // Uzavření procesu
    pclose(fp);
    
    // Vrátíme výstup (pokud je prázdný, bude to prázdný řetězec)
    return output;
}