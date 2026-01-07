#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Allocate memory for the full file path
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 for '/' and '\0'
    char *full_path = malloc(path_length);
    if (full_path == NULL) {
        return ""; // Return empty string on memory allocation failure
    }

    // Construct the full file path
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);

    // Open the file for reading
    FILE *file = fopen(full_path, "r");
    free(full_path); // Free the allocated memory for full_path
    if (file == NULL) {
        return ""; // Return empty string if the file cannot be opened
    }

    // Read the file content
    fseek(file, 0, SEEK_END); // Move to the end of the file
    long file_size = ftell(file); // Get the size of the file
    fseek(file, 0, SEEK_SET); // Move back to the beginning of the file

    // Allocate memory for the file content
    char *file_content = malloc(file_size + 1); // +1 for the null terminator
    if (file_content == NULL) {
        fclose(file);
        return ""; // Return empty string on memory allocation failure
    }

    // Read the file content into the buffer
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    return file_content; // Return the file content
}