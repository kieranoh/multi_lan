#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Dado un búfer ya lleno con un prefijo, lee el contenido de un archivo y añádelo al búfer. Luego, copia todo el búfer a otro búfer (out).

@param filename: el nombre del archivo a leer
@param out: el búfer al que copiar el contenido
@param buf: el búfer para leer el contenido del archivo
@param BUF_SIZE: el tamaño del búfer */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Contenido del archivo: ") == 14
    // buf = "Contenido del archivo: <...espacio no utilizado...>"
    // lee el contenido del archivo en buf en el desplazamiento 14
    
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Asegurar que el contenido leído esté terminado con null
    if (count < remaining) {
        buf[14 + count] = '\0';
    } else if (BUF_SIZE > 0) {
        // Si el búfer está lleno, asegurar terminación nula en el último carácter
        buf[BUF_SIZE - 1] = '\0';
    }
    
    // copia todo el contenido en buf a out
    strncpy(out, buf, BUF_SIZE);
    if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
}