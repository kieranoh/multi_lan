#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Crear un pipe para capturar la salida del comando
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Crear un proceso hijo para ejecutar el comando
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Proceso hijo
        // Cerrar el extremo de lectura del pipe
        close(pipefd[0]);
        
        // Redirigir stdout al extremo de escritura del pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Ejecutar el comando ls -l
        execlp("ls", "ls", "-l", dir_path, NULL);
        
        // Si execlp falla, salir con error
        exit(EXIT_FAILURE);
    } else {
        // Proceso padre
        // Cerrar el extremo de escritura del pipe
        close(pipefd[1]);
        
        // Leer la salida del comando
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Reasignar memoria para el resultado
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (!new_result) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read + 1);
            total_size += bytes_read;
        }
        
        // Cerrar el extremo de lectura del pipe
        close(pipefd[0]);
        
        // Esperar al proceso hijo
        int status;
        waitpid(pid, &status, 0);
        
        // Verificar si el comando se ejecutó correctamente
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            // El comando falló
            free(result);
            return strdup("");
        }
        
        // Si no se leyó nada, devolver cadena vacía
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}