#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // Määritä avaimen pituus
    const int key_length = 2048;
    
    // Luo putki (pipe) prosessien väliseen kommunikointiin
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    // Forkkaa uusi prosessi
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (pid == 0) {
        // Lasten prosessi
        
        // Sulje putken lukupää
        close(pipefd[0]);
        
        // Ohjaa stdout putkeen
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Sulje alkuperäinen kirjoituspää
        close(pipefd[1]);
        
        // Muodosta komento merkkijonona
        char command[256];
        snprintf(command, sizeof(command), 
                 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
                 key_length);
        
        // Suorita komento
        execl("/bin/sh", "sh", "-c", command, NULL);
        
        // Jos execl epäonnistuu
        exit(EXIT_FAILURE);
    } else {
        // Vanhemman prosessi
        
        // Sulje putken kirjoituspää
        close(pipefd[1]);
        
        // Lue putkesta
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            // Varmista että buffer on null-terminoitu
            buffer[bytes_read] = '\0';
            
            // Reallokoi muistia tulokselle
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (!new_result) {
                free(result);
                close(pipefd[0]);
                return NULL;
            }
            
            result = new_result;
            
            // Kopioi luettu data tulokseen
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        // Sulje putken lukupää
        close(pipefd[0]);
        
        // Odota lasten prosessin loppumista
        int status;
        waitpid(pid, &status, 0);
        
        // Tarkista että lasten prosessi päättyi onnistuneesti
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            free(result);
            return NULL;
        }
        
        // Tarkista että saatiin jotain dataa
        if (result == NULL || total_size == 0) {
            free(result);
            return NULL;
        }
        
        // Varmista että tuloksessa on PEM-muotoinen avain
        if (strstr(result, "-----BEGIN PRIVATE KEY-----") == NULL || 
            strstr(result, "-----END PRIVATE KEY-----") == NULL) {
            free(result);
            return NULL;
        }
        
        return result;
    }
}