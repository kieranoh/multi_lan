#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // Копируем префикс в буфер
    const char *prefix = "Содержимое файла: ";
    strncpy(buf, prefix, BUF_SIZE);
    
    // Читаем содержимое файла в буфер со смещением
    int prefix_len = 14; // strlen("Содержимое файла: ")
    int remaining = BUF_SIZE - prefix_len - 1; // -1 для завершающего нуля
    if (remaining > 0) {
        int count = read(fd, buf + prefix_len, remaining);
        if (count < 0) {
            perror("Error reading file");
            close(fd);
            return;
        }
        // Гарантируем, что строка завершается нулем
        if (prefix_len + count < BUF_SIZE) {
            buf[prefix_len + count] = '\0';
        } else {
            buf[BUF_SIZE - 1] = '\0';
        }
    } else {
        // Если места нет, просто завершаем строку
        if (BUF_SIZE > 0) {
            buf[BUF_SIZE - 1] = '\0';
        }
    }
    
    close(fd);
    
    // Копируем все содержимое из buf в out
    strncpy(out, buf, BUF_SIZE);
    if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
}