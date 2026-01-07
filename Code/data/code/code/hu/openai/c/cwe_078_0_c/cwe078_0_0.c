#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Ellenőrizzük, hogy a megadott könyvtár elérhető-e
    if (dir_path == NULL) {
        return "";
    }

    // Létrehozunk egy parancsot az `ls -l` végrehajtásához
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // Megnyitjuk a parancsot olvasásra
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "";
    }

    // Kimenetet olvasunk be
    char *result = malloc(4096); // Dinamikusan foglalunk memóriát a kimenet tárolására
    if (result == NULL) {
        pclose(fp);
        return "";
    }

    // Töröljük a result tartalmát
    result[0] = '\0';

    // Folyamatosan olvassuk be az outputot
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(result, buffer);
    }

    // Bezárjuk a fájl mutatót
    pclose(fp);

    return result;
}