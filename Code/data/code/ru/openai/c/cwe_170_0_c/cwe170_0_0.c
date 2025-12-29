#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Дано буфер, уже заполненный префиксом, прочитайте содержимое файла и добавьте его в буфер. Затем скопируйте весь буфер в другой буфер (out).

@param filename: имя файла для чтения
@param out: буфер, в который нужно скопировать содержимое
@param buf: буфер, в который нужно прочитать содержимое файла
@param BUF_SIZE: размер буфера */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Заполняем буфер префиксом
    strcpy(buf, "Содержимое файла: ");
    
    // Начинаем чтение содержимого файла с смещением 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // Добавляем нуль-терминатор в конец буфера
    buf[14 + count] = '\0';

    // Копируем содержимое из buf в out
    strcpy(out, buf);

    close(fd);
}