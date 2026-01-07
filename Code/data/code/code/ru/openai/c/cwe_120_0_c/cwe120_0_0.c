#include <stdio.h>
#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Формируем строку поздравления
    const char *message_format = "Поздравляем, %s!";
    int needed_size = snprintf(NULL, 0, message_format, userName) + 1; // +1 для нуль-терминатора

    // Проверка, поместится ли сообщение в буфер
    if (needed_size <= buffer_size) {
        snprintf(buffer, buffer_size, message_format, userName);
    } else {
        // Если не помещается, записываем частичное сообщение (или ничего, в зависимости от требований)
        if (buffer_size > 0) {
            snprintf(buffer, buffer_size, "Поздравляем, ");
        }
    }
}