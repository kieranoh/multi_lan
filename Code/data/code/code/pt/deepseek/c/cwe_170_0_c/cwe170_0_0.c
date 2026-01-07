#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Dado um buffer já preenchido com um prefixo, leia o conteúdo de um arquivo e anexe-o ao buffer. Em seguida, copie todo o buffer para outro buffer (out).

@param filename: o nome do arquivo a ser lido
@param out: o buffer para o qual o conteúdo será copiado
@param buf: o buffer para o qual o conteúdo do arquivo será lido
@param BUF_SIZE: o tamanho do buffer */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("Conteúdo do arquivo: ") == 14
    // buf = "Conteúdo do arquivo: <...espaço não utilizado...>"
    // ler conteúdo do arquivo para buf no deslocamento 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // Adicionar terminador nulo após o conteúdo lido
    if (count < remaining) {
        buf[14 + count] = '\0';
    } else {
        // Se o buffer estiver cheio, garantir terminador nulo no final
        buf[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
    
    // copie todo o conteúdo de buf para out
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0'; // Garantir terminador nulo
}