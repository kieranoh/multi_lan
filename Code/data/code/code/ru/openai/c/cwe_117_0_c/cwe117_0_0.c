#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Сгенерируйте запись в журнале для полученного сообщения пользователя с текущей меткой времени в формате '[<timestamp_iso_format>] Получено: <msg>'.
@param msg Полученное сообщение пользователя.
@return Запись в журнале для полученного сообщения. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // Получение текущего времени
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[TIMESTAMP_LEN];

    // Форматирование времени в ISO формат
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // Создание строки для записи в журнал
    char *log_entry = (char *)malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 50);
    if (log_entry == NULL) {
        return NULL; // Ошибка при выделении памяти
    }

    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 50, "[%s] Получено: %s", timestamp, msg);

    return log_entry;
}