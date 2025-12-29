#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_ls_result(const char *dir_path) {
    // Spremimo izlaz u privremeni datoteku
    FILE *fp;
    char *result = NULL;
    char buffer[1024];
    char command[1024];

    // Formiramo naredbu
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // Otvorimo cjevovod za izvođenje naredbe
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Vratimo prazan niz u slučaju pogreške
    }

    // Čitamo izlaz
    size_t len = 0;
    size_t total_len = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        len = strlen(buffer);
        char *temp = realloc(result, total_len + len + 1);
        if (temp == NULL) {
            free(result);
            pclose(fp);
            return ""; // Vratimo prazan niz ako dođe do pogreške u alokaciji
        }
        result = temp;
        strcpy(result + total_len, buffer);
        total_len += len;
    }

    // Zatvaramo cjevovod
    pclose(fp);

    // Osiguravamo da je rezultat ispravno završen sa '\0'
    if (result != NULL) {
        result[total_len] = '\0';
    }

    return result; // Vraćamo rezultat
}