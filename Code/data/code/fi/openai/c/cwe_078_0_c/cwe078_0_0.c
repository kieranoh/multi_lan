#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Varaamme tilaa tulostetta varten
    char *output = malloc(1024 * sizeof(char));
    if (output == NULL) {
        return ""; // Palautetaan tyhjää merkkijonoa, jos muistin varaus epäonnistuu
    }
    
    // Komento ls -l hakemistopolulle
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Suoritetaan komento
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output);
        return ""; // Palautetaan tyhjää merkkijonoa virhetilanteessa
    }

    // Luetaan komennon tuloste
    size_t index = 0;
    while (fgets(output + index, 1024 - index, fp) != NULL) {
        index += strlen(output + index);
        if (index >= 1024) {
            break; // Varmistetaan, että emme ylitä varattua tilaa
        }
    }

    // Suljetaan prosessi
    pclose(fp);

    return output; // Palautetaan komennon tuloste
}