#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Create the full file path
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // +2 for '/' and '\0'
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return ""; // Return empty string on memory allocation failure
    }
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);

    // Open the file for reading
    FILE *file = fopen(full_path, "r");
    free(full_path); // Free the full_path after use
    if (file == NULL) {
        return ""; // Return empty string if file cannot be opened
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET); // Go back to the beginning of the file

    // Allocate memory for the file content
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // Return empty string on memory allocation failure
    }

    // Read the file content into the allocated memory
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);
    
    return content; // Return the file content
}