#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Izveidojam komandas virkni
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Atveram cauruli, lai izsauktu komandu
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Ja rodas kļūda, atgriežam tukšu virkni
    }

    // Lasām komandas izeju
    char *result = malloc(1024 * sizeof(char)); // Atļaujam 1024 baitu atmiņu rezultātam
    if (result == NULL) {
        pclose(fp);
        return ""; // Ja neatceram atmiņu, atgriežam tukšu virkni
    }

    // Ievietojam izeju rezultātā
    size_t total_length = 0;
    while (fgets(result + total_length, 1024, fp) != NULL) {
        total_length += strlen(result + total_length);
        if (total_length + 1024 >= sizeof(result)) {
            // Ja nepieciešams vairāk vietas, pārrakstām rezultātu
            char *new_result = realloc(result, total_length + 1024);
            if (new_result == NULL) {
                free(result);
                pclose(fp);
                return ""; // Ja neatceram atmiņu, atgriežam tukšu virkni
            }
            result = new_result;
        }
    }

    // Caurules slēgšana
    pclose(fp);

    // Atgriežam rezultātu
    return result;
}