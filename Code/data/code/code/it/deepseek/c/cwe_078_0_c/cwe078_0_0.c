#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Creiamo una pipe per catturare l'output
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) { // Processo figlio
        // Chiudiamo l'estremità di lettura della pipe
        close(pipefd[0]);
        
        // Reindirizziamo stdout alla pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Chiudiamo l'originale pipefd[1] dopo dup2
        close(pipefd[1]);
        
        // Cambiamo directory se specificata
        if (dir_path != NULL && strlen(dir_path) > 0) {
            if (chdir(dir_path) != 0) {
                exit(EXIT_FAILURE);
            }
        }
        
        // Eseguiamo ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Se arriviamo qui, execlp ha fallito
        exit(EXIT_FAILURE);
    } else { // Processo padre
        // Chiudiamo l'estremità di scrittura della pipe
        close(pipefd[1]);
        
        // Leggiamo l'output dal comando
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        // Chiudiamo l'estremità di lettura della pipe
        close(pipefd[0]);
        
        // Aspettiamo che il processo figlio termini
        int status;
        waitpid(pid, &status, 0);
        
        // Controlliamo se il comando è stato eseguito con successo
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // Se non abbiamo letto nulla, restituiamo stringa vuota
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}