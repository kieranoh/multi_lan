#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Provera da li je putanja NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    int pipefd[2];
    pid_t pid;
    
    // Kreiranje pipe-a za komunikaciju između procesa
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Kreiranje dete procesa
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Dete proces
        close(pipefd[0]); // Zatvaramo čitanje iz pipe-a
        
        // Preusmeravanje stdout-a na pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // Zatvaramo originalni pipefd[1] nakon dup2
        close(pipefd[1]);
        
        // Menjamo direktorijum
        if (chdir(dir_path) != 0) {
            _exit(EXIT_FAILURE);
        }
        
        // Izvršavamo ls -l komandu
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Ako dođemo ovde, execlp je pao
        _exit(EXIT_FAILURE);
    } else {
        // Roditelj proces
        close(pipefd[1]); // Zatvaramo pisanje u pipe
        
        // Čitamo iz pipe-a
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *result = malloc(1);
        
        if (result == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        result[0] = '\0';
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Realociramo memoriju za novi sadržaj
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            strcpy(result + total_size, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // Čekamo da dete proces završi i proveravamo status
        int status;
        waitpid(pid, &status, 0);
        
        // Proveravamo da li je komanda uspešno izvršena
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return result;
        } else {
            free(result);
            return strdup("");
        }
    }
}