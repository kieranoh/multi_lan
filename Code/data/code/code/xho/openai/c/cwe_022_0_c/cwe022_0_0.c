#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Create the full file path
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);

    // Open the file for reading
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        // Return an empty string if the file cannot be opened
        return strdup("");
    }

    // Allocate memory to hold the file contents
    fseek(file, 0, SEEK_END); // Move to the end of the file
    long file_size = ftell(file); // Get the size of the file
    fseek(file, 0, SEEK_SET); // Move back to the beginning of the file

    char *content = (char *)malloc(file_size + 1); // +1 for the null terminator
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }

    // Read the file contents into the buffer
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string

    fclose(file); // Close the file
    return content; // Return the content
}