#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Bide osoa eraikitzeko bufferra
    char full_path[1024];
    
    // Bide osoa eraiki
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= (int)sizeof(full_path)) {
        // Buffer gainezka - itzuli string hutsa
        return strdup("");
    }
    
    // Fitxategia existitzen den eta irakurri daitekeen egiaztatu
    struct stat file_stat;
    if (stat(full_path, &file_stat) != 0) {
        // Fitxategia ez da existitzen edo sarbide errorea
        return strdup("");
    }
    
    // Fitxategia arrunta den eta irakurri daitekeen egiaztatu
    if (!S_ISREG(file_stat.st_mode)) {
        // Ez da fitxategi arrunta
        return strdup("");
    }
    
    // Fitxategia ireki
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        // Ezin izan da ireki
        return strdup("");
    }
    
    // Fitxategiaren tamaina lortu
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        // Tamaina ezin izan da zehaztu
        fclose(file);
        return strdup("");
    }
    
    // Memoria erreserbatu edukia gordetzeko (null terminatorra barne)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        // Memoria erreserba huts egin du
        fclose(file);
        return strdup("");
    }
    
    // Fitxategia irakurri
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        // Irakurketak huts egin du
        free(content);
        return strdup("");
    }
    
    // Null terminatorra gehitu
    content[file_size] = '\0';
    
    return content;
}