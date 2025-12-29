#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Sprawdź, czy ścieżka jest NULL
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Utwórz potok do przechwytywania wyjścia polecenia
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Utwórz proces potomny
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Proces potomny
        // Zamknij koniec odczytu potoku
        close(pipefd[0]);
        
        // Przekieruj stdout do potoku
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // Zamknij niepotrzebny deskryptor
        close(pipefd[1]);
        
        // Zmień katalog roboczy
        if (chdir(dir_path) != 0) {
            _exit(EXIT_FAILURE);
        }
        
        // Wykonaj polecenie ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Jeśli execlp zawiedzie
        _exit(EXIT_FAILURE);
    } else {
        // Proces rodzica
        // Zamknij koniec zapisu potoku
        close(pipefd[1]);
        
        // Odczytaj dane z potoku
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Realokuj pamięć dla wyniku
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
        
        // Zamknij koniec odczytu potoku
        close(pipefd[0]);
        
        // Poczekaj na zakończenie procesu potomnego
        int status;
        waitpid(pid, &status, 0);
        
        // Sprawdź, czy polecenie zakończyło się sukcesem
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result != NULL) {
            return result;
        } else {
            free(result);
            return strdup("");
        }
    }
}