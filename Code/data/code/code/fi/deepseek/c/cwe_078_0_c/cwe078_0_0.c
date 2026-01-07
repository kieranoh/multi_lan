#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Tarkista, että dir_path ei ole NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Luo putki (pipe) kommunikointia varten
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Luo uusi prosessi
    pid_t pid = fork();
    
    if (pid == -1) {
        // fork epäonnistui
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Lapsiprosessi
        
        // Sulje putken lukupää
        close(pipefd[0]);
        
        // Ohjaa stdout putkeen
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // Sulje putken kirjoituspää (nyt duplikattu stdout:ksi)
        close(pipefd[1]);
        
        // Suorita ls -l -komento
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // Jos execlp epäonnistuu, poistu
        _exit(EXIT_FAILURE);
    } else {
        // Vanhempiprosessi
        
        // Sulje putken kirjoituspää
        close(pipefd[1]);
        
        // Lue tuloste putkesta
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *result = NULL;
        char *temp = NULL;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            temp = realloc(result, total_size + bytes_read + 1);
            if (temp == NULL) {
                free(result);
                close(pipefd[0]);
                return strdup("");
            }
            
            result = temp;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        // Sulje putken lukupää
        close(pipefd[0]);
        
        // Odota lapsiprosessin päättymistä
        int status;
        waitpid(pid, &status, 0);
        
        // Tarkista, että komento suoritettiin onnistuneesti
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Jos ei luettu mitään, palauta tyhjä merkkijono
            if (result == NULL) {
                return strdup("");
            }
            return result;
        } else {
            // Komento epäonnistui
            free(result);
            return strdup("");
        }
    }
}