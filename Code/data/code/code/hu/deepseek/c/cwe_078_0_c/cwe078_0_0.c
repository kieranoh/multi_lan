#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    int pipefd[2];
    pid_t pid;
    char *result = NULL;
    size_t result_size = 0;
    size_t result_len = 0;
    char buffer[4096];
    ssize_t bytes_read;
    
    // Ellenőrizzük, hogy a dir_path NULL-e
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Pipe létrehozása
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Gyermek folyamat létrehozása
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Gyermek folyamat
        close(pipefd[0]); // Olvasási vége nem kell
        
        // Átirányítjuk a stdout-ot a pipe író végére
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Könyvtárváltás
        if (chdir(dir_path) != 0) {
            exit(EXIT_FAILURE);
        }
        
        // ls -l parancs végrehajtása
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Ha ide érünk, az execlp hibázott
        exit(EXIT_FAILURE);
    } else {
        // Szülő folyamat
        close(pipefd[1]); // Író vége nem kell
        
        // Olvassuk a pipe-ból az eredményt
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            // Nulla terminálás a biztonság kedvéért
            buffer[bytes_read] = '\0';
            
            // Ellenőrizzük, hogy van-e elegendő hely az eredményben
            if (result_len + bytes_read + 1 > result_size) {
                size_t new_size = result_size == 0 ? 1024 : result_size * 2;
                char *new_result = realloc(result, new_size);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
                result_size = new_size;
            }
            
            // Másoljuk az adatokat az eredménybe
            memcpy(result + result_len, buffer, bytes_read);
            result_len += bytes_read;
            result[result_len] = '\0';
        }
        
        close(pipefd[0]);
        
        // Várjuk meg a gyermek folyamatot
        int status;
        waitpid(pid, &status, 0);
        
        // Ha a gyermek folyamat nem terminált normálisan, vagy hibával terminált
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // Ha nem olvastunk semmit, adjunk vissza üres stringet
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}