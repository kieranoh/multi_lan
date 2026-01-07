#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    // Comando para gerar uma chave RSA privada usando OpenSSL
    const char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 -outform PEM 2>/dev/null";
    
    // Buffer para armazenar a saída do comando
    char *buffer = NULL;
    size_t size = 0;
    
    // Abrindo um pipe para o comando
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return NULL; // Retorna NULL se não conseguiu abrir o pipe
    }
    
    // Lendo a saída do comando
    while (getline(&buffer, &size, pipe) != -1) {
        // Realiza a leitura da saída
    }
    
    // Fecha o pipe
    if (pclose(pipe) == -1) {
        free(buffer);
        return NULL; // Retorna NULL se houve um erro ao fechar o pipe
    }

    // Retorna a chave privada como uma string
    return buffer;
}