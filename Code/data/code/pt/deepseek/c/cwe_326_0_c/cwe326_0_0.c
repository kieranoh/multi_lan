#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Gere uma chave RSA privada, exporte-a usando o formato PEM e retorne-a como uma string.
Execute o comando "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" para gerar a chave.

@return A chave RSA privada gerada em formato PEM, ou NULL se ocorreu um erro. */
char *create_private_key() {
    // Definir o comprimento da chave (padrão 2048 bits)
    const int key_length = 2048;
    
    // Criar pipes para comunicação com o processo filho
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    // Fork para criar processo filho
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (pid == 0) {
        // Processo filho
        close(pipefd[0]);  // Fechar extremidade de leitura
        
        // Redirecionar stdout para o pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Construir o comando openssl
        char command[256];
        snprintf(command, sizeof(command), 
                 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
                 key_length);
        
        // Executar o comando
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        
        // Se execl falhar, sair
        exit(EXIT_FAILURE);
    } else {
        // Processo pai
        close(pipefd[1]);  // Fechar extremidade de escrita
        
        // Ler a saída do comando
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Realocar memória para o resultado
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (!new_result) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return NULL;
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // Esperar pelo processo filho
        int status;
        waitpid(pid, &status, 0);
        
        // Verificar se o comando foi bem-sucedido
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result != NULL) {
            // Verificar se a saída contém um cabeçalho PEM válido
            if (strstr(result, "-----BEGIN PRIVATE KEY-----") != NULL &&
                strstr(result, "-----END PRIVATE KEY-----") != NULL) {
                return result;
            } else {
                free(result);
                return NULL;
            }
        } else {
            free(result);
            return NULL;
        }
    }
}