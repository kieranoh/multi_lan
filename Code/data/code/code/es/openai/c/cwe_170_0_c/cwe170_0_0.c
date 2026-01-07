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
    
    // Inicializa el buf con el prefijo
    const char *prefix = "Contenido del archivo: ";
    strncpy(buf, prefix, BUF_SIZE);
    
    // Asegúrate de que el espacio esté disponible después del prefijo
    int remaining = BUF_SIZE - strlen(prefix) - 1; // -1 para el carácter nulo
    int count = read(fd, buf + strlen(prefix), remaining);
    
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Asegúrate de que el búfer esté correctamente terminado en nulo
    buf[strlen(prefix) + count] = '\0';
    
    // Copia todo el contenido en buf a out
    strncpy(out, buf, BUF_SIZE);
    
    close(fd);
}