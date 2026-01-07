#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Skapa den fullständiga sökvägen till filen
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Öppna filen för skrivning, skapa den om den inte finns
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Kunde inte öppna filen för skrivning");
        return;
    }

    // Skriv innehållet till filen
    fprintf(file, "%s", content);
    
    // Stäng filen
    fclose(file);

    // Ändra filrättigheterna så att endast ägaren kan läsa och skriva
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Kunde inte ändra filrättigheterna");
    }
}