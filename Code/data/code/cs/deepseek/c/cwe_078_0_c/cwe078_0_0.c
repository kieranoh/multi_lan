#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Vytvoření anonymního kanálu pro komunikaci mezi procesy
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Vytvoření nového procesu
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Dětský proces
        close(pipefd[0]); // Zavřeme čtecí konec
        
        // Přesměrování stdout na zápisový konec kanálu
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Změna pracovního adresáře
        if (chdir(dir_path) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Spuštění příkazu ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Pokud execlp selže
        exit(EXIT_FAILURE);
    } else {
        // Rodičovský proces
        close(pipefd[1]); // Zavřeme zápisový konec
        
        // Čtení výstupu z kanálu
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (!new_result) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // Čekání na dokončení dětského procesu
        int status;
        waitpid(pid, &status, 0);
        
        // Kontrola, zda příkaz proběhl úspěšně
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result) {
            return result;
        } else {
            free(result);
            return strdup("");
        }
    }
}