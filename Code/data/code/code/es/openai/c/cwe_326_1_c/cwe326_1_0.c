#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);

    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up on error
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up on error
        return NULL;
    }

    char* private_key = execute_command("cat /tmp/dsa_private.pem");
    unlink(param_filename); // Clean up parameters file
    unlink("/tmp/dsa_private.pem"); // Clean up private key file

    return private_key;
}