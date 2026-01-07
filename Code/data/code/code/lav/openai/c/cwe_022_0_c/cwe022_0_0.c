#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Uzbūvē ceļu uz failu
    size_t path_size = strlen(dir_path) + strlen(filename) + 2; // +2 par '/' un '\0'
    char *full_path = (char *)malloc(path_size);
    if (full_path == NULL) {
        return ""; // Atgriežam tukšu virkni, ja malloc neizdodas
    }
    
    snprintf(full_path, path_size, "%s/%s", dir_path, filename);
    
    // Atveram failu lasīšanai
    FILE *file = fopen(full_path, "r");
    free(full_path); // Atbrīvojam ceļa virkni, jo tā vairs nav nepieciešama
    if (file == NULL) {
        return ""; // Atgriežam tukšu virkni, ja fails nav atrodams vai nevaram to atvērt
    }

    // Nosakām faila lielumu
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Izveidojam bufferi faila saturam
    char *buffer = (char *)malloc(file_size + 1); // +1 par null terminatoru
    if (buffer == NULL) {
        fclose(file);
        return ""; // Atgriežam tukšu virkni, ja malloc neizdodas
    }

    // Nolasām faila saturu
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Pievienojam null terminatoru

    fclose(file); // Aizveram failu
    return buffer; // Atgriežam nolasīto saturu
}