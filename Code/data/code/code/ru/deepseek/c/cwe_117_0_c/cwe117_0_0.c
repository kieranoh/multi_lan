#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Получаем текущее время
    time_t raw_time;
    struct tm *time_info;
    char timestamp[20];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Форматируем время в ISO формате (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    // Вычисляем необходимую длину строки
    // [timestamp] Получено: msg\0
    size_t msg_len = strlen(msg);
    size_t total_len = 1 + strlen(timestamp) + 1 + 11 + 2 + msg_len + 1; // [ + timestamp + ] + " Получено: " + msg + \0
    
    // Проверяем длину сообщения
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    // Выделяем память для результата
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Формируем запись журнала
    snprintf(log_entry, total_len, "[%s] Получено: %s", timestamp, msg);
    
    return log_entry;
}