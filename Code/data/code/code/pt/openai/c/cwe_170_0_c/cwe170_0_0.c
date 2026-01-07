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

    // Prefixo a ser adicionado ao buffer
    const char *prefix = "Conteúdo do arquivo: ";
    int prefix_len = strlen(prefix);
    
    // Verifica se o tamanho do buffer é suficiente
    if (BUF_SIZE <= prefix_len) {
        perror("Buffer size is too small");
        close(fd);
        return;
    }

    // Copia o prefixo para o buffer
    strncpy(buf, prefix, prefix_len);
    
    // Calcula o espaço restante no buffer
    int remaining = BUF_SIZE - prefix_len;
    
    // Lê o conteúdo do arquivo para buf no deslocamento do prefixo
    int count = read(fd, buf + prefix_len, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Adiciona um terminador nulo para garantir que o buffer seja uma string válida
    buf[prefix_len + count] = '\0';

    // Copie todo o conteúdo de buf para out
    strncpy(out, buf, BUF_SIZE);

    // Fecha o arquivo
    close(fd);
}