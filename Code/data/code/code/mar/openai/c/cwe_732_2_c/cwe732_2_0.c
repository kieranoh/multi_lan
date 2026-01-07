#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // Create the full path for the secret file
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    // Write the content to the file
    fputs(content, file);

    // Close the file
    fclose(file);

    // Change the file permissions to make it accessible only to the user
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("Failed to set file permissions");
    }
}