#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Prepare the command string
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // Open the command for reading
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "";
    }

    // Allocate memory for the output
    char *output = malloc(1024 * sizeof(char)); // Allocate 1KB for output
    if (output == NULL) {
        pclose(fp);
        return "";
    }

    // Read the output a line at a time - output it.
    size_t total_size = 0;
    size_t read_size;
    while (fgets(output + total_size, 1024, fp) != NULL) {
        total_size += strlen(output + total_size);
        // Reallocate more memory if needed
        if (total_size + 1024 > sizeof(output)) {
            char *new_output = realloc(output, total_size + 1024);
            if (new_output == NULL) {
                free(output);
                pclose(fp);
                return "";
            }
            output = new_output;
        }
    }

    // Close the command stream
    pclose(fp);

    // Return the output
    return output;
}