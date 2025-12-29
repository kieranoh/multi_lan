#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Vérifier si le chemin est NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Créer un tube pour capturer la sortie
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Forker le processus
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Processus enfant
        close(pipefd[0]);  // Fermer l'extrémité de lecture
        
        // Rediriger stdout vers le tube
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Exécuter la commande ls -l
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // Si execlp échoue, quitter avec un code d'erreur
        exit(EXIT_FAILURE);
    } else {
        // Processus parent
        close(pipefd[1]);  // Fermer l'extrémité d'écriture
        
        // Lire la sortie du tube
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *output = NULL;
        char *temp;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            temp = realloc(output, total_size + bytes_read + 1);
            if (temp == NULL) {
                free(output);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            output = temp;
            memcpy(output + total_size, buffer, bytes_read);
            total_size += bytes_read;
            output[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // Attendre la fin du processus enfant
        int status;
        waitpid(pid, &status, 0);
        
        // Vérifier si la commande a réussi
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(output);
            return strdup("");
        }
        
        // Si aucune sortie n'a été lue, retourner une chaîne vide
        if (output == NULL) {
            return strdup("");
        }
        
        return output;
    }
}