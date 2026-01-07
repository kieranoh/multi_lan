#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    FILE *fp;
    char command[256];
    char *result = NULL;
    size_t result_size = 0;
    size_t read;

    // Create the command string
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Return empty string on error
    }

    // Read the output a line at a time - output it.
    char buffer[1024];
    while ((read = fread(buffer, 1, sizeof(buffer) - 1, fp)) > 0) {
        buffer[read] = '\0';
        size_t current_length = result_size;
        result_size += read;
        result = realloc(result, result_size + 1); // +1 for null terminator
        if (result == NULL) {
            pclose(fp);
            return ""; // Return empty string on memory allocation error
        }
        memcpy(result + current_length, buffer, read);
        result[current_length + read] = '\0';
    }

    // Close the command stream
    pclose(fp);

    // If result is NULL, it means there was no output
    if (result == NULL || strlen(result) == 0) {
        return ""; // Return empty string if no output
    }

    return result;
}