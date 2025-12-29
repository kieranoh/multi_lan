#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Erstelle eine Pipe für die Kommunikation zwischen Eltern- und Kindprozess
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Forke einen Kindprozess
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) { // Kindprozess
        // Schließe das Lesende der Pipe
        close(pipefd[0]);
        
        // Leite stdout zur Pipe um
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Schließe das Schreibende der Pipe nach der Umleitung
        close(pipefd[1]);
        
        // Ändere das Verzeichnis
        if (chdir(dir_path) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Führe ls -l aus
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // Wenn execlp fehlschlägt
        exit(EXIT_FAILURE);
    } else { // Elternprozess
        // Schließe das Schreibende der Pipe
        close(pipefd[1]);
        
        // Lese die Ausgabe von der Pipe
        char buffer[4096];
        size_t total_size = 0;
        size_t buffer_capacity = 4096;
        char *result = malloc(buffer_capacity);
        
        if (result == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Überprüfe, ob genug Speicher vorhanden ist
            if (total_size + bytes_read + 1 > buffer_capacity) {
                buffer_capacity = (total_size + bytes_read + 1) * 2;
                char *new_result = realloc(result, buffer_capacity);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
            }
            
            // Füge die gelesenen Daten zum Ergebnis hinzu
            strcat(result, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // Warte auf den Kindprozess und prüfe seinen Exit-Status
        int status;
        waitpid(pid, &status, 0);
        
        // Wenn der Kindprozess fehlgeschlagen ist, gib einen leeren String zurück
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // Stelle sicher, dass der String null-terminiert ist
        if (total_size == 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}