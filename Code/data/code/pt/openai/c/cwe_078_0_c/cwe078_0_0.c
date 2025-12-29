#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    // Cria um buffer para armazenar a saída do comando
    char *output = (char *)malloc(BUFFER_SIZE);
    if (!output) {
        return "";
    }

    // Comando a ser executado
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s 2>&1", dir_path);
    
    // Abre um pipe para o comando
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output);
        return "";
    }

    // Lê a saída do comando
    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(output + total_read, 1, BUFFER_SIZE - total_read, fp)) > 0) {
        total_read += bytes_read;
        if (total_read >= BUFFER_SIZE) {
            break; // Evitar overflow do buffer
        }
    }
    output[total_read] = '\0'; // Garantir que a string esteja terminada

    // Fecha o pipe
    pclose(fp);

    // Se não houve leitura (erro de execução), retorna string vazia
    if (total_read == 0) {
        free(output);
        return "";
    }

    return output;
}