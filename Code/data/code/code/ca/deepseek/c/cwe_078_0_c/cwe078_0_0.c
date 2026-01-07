#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Crear una pipe per llegir la sortida del fill
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
    
    if (pid == 0) {  // Procés fill
        // Tancar el costat de lectura de la pipe
        close(pipefd[0]);
        
        // Redirigir stdout a la pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Tancar el descriptor original després del dup2
        close(pipefd[1]);
        
        // Executar ls -l amb el directori proporcionat
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // Si arribem aquí, execlp ha fallat
        exit(EXIT_FAILURE);
    } else {  // Procés pare
        // Tancar el costat d'escriptura de la pipe
        close(pipefd[1]);
        
        // Llegir la sortida del fill
        char buffer[4096];
        size_t total_size = 0;
        char *output = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Reassignar memòria per a la sortida completa
            char *new_output = realloc(output, total_size + bytes_read + 1);
            if (new_output == NULL) {
                free(output);
                close(pipefd[0]);
                return strdup("");
            }
            
            output = new_output;
            memcpy(output + total_size, buffer, bytes_read);
            total_size += bytes_read;
            output[total_size] = '\0';
        }
        
        // Tancar el costat de lectura de la pipe
        close(pipefd[0]);
        
        // Esperar al procés fill i verificar l'estat de sortida
        int status;
        waitpid(pid, &status, 0);
        
        // Si el procés fill no ha sortit correctament, retornar cadena buida
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            free(output);
            return strdup("");
        }
        
        // Si no hi ha sortida, retornar cadena buida
        if (output == NULL) {
            return strdup("");
        }
        
        return output;
    }
}