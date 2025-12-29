#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Declaração da função para executar um comando shell e capturar sua saída
char* execute_command(const char* command);

/* Gere uma chave DSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
   @return A chave privada DSA gerada no formato PEM, ou NULL se ocorreu um erro. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Erro ao criar arquivo temporário
    }
    close(fd);

    // Comando para gerar os parâmetros DSA
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command1) == NULL) {
        unlink(param_filename); // Remove o arquivo se houver um erro
        return NULL;
    }

    // Comando para gerar a chave privada DSA
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -outform PEM -out /dev/stdout %s", param_filename);
    char* private_key = execute_command(command2);
    
    unlink(param_filename); // Remove o arquivo temporário
    return private_key; // Retorna a chave privada DSA em formato PEM
}