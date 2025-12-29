#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Fitxategi bide osoa sortu
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Fitxategia sortu eta datuak idatzi
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Fitxategia sortzeko akatsa");
        return;
    }
    
    // Edukia idatzi fitxategian
    fprintf(file, "%s", content);
    fclose(file);

    // Fitxategiaren baimenen konfigurazioa (irakurri eta idazteko baimena, beste guztientzat ukatuta)
    chmod(filepath, S_IRUSR | S_IWUSR);
}