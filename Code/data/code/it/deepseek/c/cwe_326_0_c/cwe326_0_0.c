#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *create_private_key() {
    // Lunghezza della chiave RSA (2048 bit è un valore standard sicuro)
    const int key_length = 2048;
    
    // Crea un pipe per catturare l'output del comando
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (pid == 0) {
        // Processo figlio
        close(pipefd[0]); // Chiudi l'estremità di lettura
        
        // Reindirizza stdout al pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Costruisci il comando
        char command[256];
        snprintf(command, sizeof(command), 
                "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
                key_length);
        
        // Esegui il comando
        execl("/bin/sh", "sh", "-c", command, NULL);
        
        // Se arriviamo qui, execl ha fallito
        exit(EXIT_FAILURE);
    } else {
        // Processo padre
        close(pipefd[1]); // Chiudi l'estremità di scrittura
        
        // Leggi l'output dal pipe
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *result = NULL;
        char *temp_result = NULL;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            temp_result = realloc(result, total_size + bytes_read + 1);
            if (temp_result == NULL) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return NULL;
            }
            
            result = temp_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // Attendi che il processo figlio termini
        int status;
        waitpid(pid, &status, 0);
        
        // Verifica se il comando è stato eseguito con successo
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result != NULL) {
            // Verifica che l'output contenga effettivamente una chiave PEM
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