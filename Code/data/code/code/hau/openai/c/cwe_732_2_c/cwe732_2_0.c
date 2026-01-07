#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Create the full path for the secret file
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the content to the file
    fprintf(file, "%s", content);
    fclose(file);

    // Set file permissions to be accessible only by the owner
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("Error setting file permissions");
    }
}