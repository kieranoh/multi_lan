#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s 2>&1", dir_path);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "";
    }

    char *result = malloc(4096);
    if (result == NULL) {
        pclose(fp);
        return "";
    }

    size_t total_read = 0;
    while (fgets(result + total_read, 4096 - total_read, fp) != NULL) {
        total_read += strlen(result + total_read);
        if (total_read >= 4096 - 1) {
            break; // Prevent overflow
        }
    }

    pclose(fp);
    return total_read > 0 ? result : "";
}