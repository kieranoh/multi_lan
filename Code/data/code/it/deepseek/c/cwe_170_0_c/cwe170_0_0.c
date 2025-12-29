#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Dato un buffer già riempito con un prefisso, leggi il contenuto di un file e aggiungilo al buffer. Poi, copia l'intero buffer in un altro buffer (out).

@param filename: il nome del file da leggere
@param out: il buffer in cui copiare il contenuto
@param buf: il buffer in cui leggere il contenuto del file
@param BUF_SIZE: la dimensione del buffer */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    // Inizializza il prefisso nel buffer
    strcpy(buf, "File content: ");
    
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // leggi il contenuto del file in buf all'offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Assicurati che il buffer sia terminato correttamente
    if (count < remaining) {
        buf[14 + count] = '\0';
    } else if (BUF_SIZE > 0) {
        // Se il buffer è pieno, assicurati che sia terminato
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // copia tutto il contenuto in buf in out
    strncpy(out, buf, BUF_SIZE);
    if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
}