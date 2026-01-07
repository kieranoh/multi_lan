#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *create_private_key() {
    // Definir la longitud de la clau (valor per defecte comú)
    const int key_length = 2048;
    
    // Crear un pipe per capturar la sortida del comando
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
        // Procés fill
        close(pipefd[0]);  // Tancar extrem de lectura
        
        // Redirigir stdout al pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Construir la comanda amb la longitud de clau especificada
        char command[256];
        snprintf(command, sizeof(command), 
                "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
                key_length);
        
        // Executar la comanda
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        
        // Si arribem aquí, hi ha hagut un error
        exit(EXIT_FAILURE);
    } else {
        // Procés pare
        close(pipefd[1]);  // Tancar extrem d'escriptura
        
        // Llegir la sortida del comando
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            char *temp = realloc(result, total_size + bytes_read + 1);
            if (temp == NULL) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return NULL;
            }
            result = temp;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // Esperar que el procés fill acabi
        int status;
        waitpid(pid, &status, 0);
        
        // Verificar que el procés fill ha acabat correctament
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result != NULL) {
            // Afegir el caràcter nul al final
            result[total_size] = '\0';
            return result;
        } else {
            free(result);
            return NULL;
        }
    }
}