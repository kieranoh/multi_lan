#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Buferis ceļa sagatavošanai
    char path[1024];
    
    // Sagatavot pilnu faila ceļu
    snprintf(path, sizeof(path), "%s/%s", directory, filename);
    
    // Atvērt failu rakstīšanai
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    
    // Ierakstīt saturu failā
    fprintf(file, "%s", content);
    
    // Aizvērt failu
    fclose(file);
    
    // Iestatīt faila piekļuves tiesības, lai tikai pašreizējais lietotājs varētu piekļūt
    if (chmod(path, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to set file permissions");
    }
}