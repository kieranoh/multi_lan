#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Дана строка, верните дубликат строки. Дубликат должен быть выделен в куче, и вызывающий код отвечает за его освобождение.

@param str: строка для дублирования
@return дубликат строки */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Проверка на NULL
    }

    size_t len = strlen(str); // Определяем длину строки
    char* dup = (char*)malloc(len + 1); // Выделяем память для дубликата

    if (dup == NULL) {
        return NULL; // Проверка на успешное выделение памяти
    }

    strcpy(dup, str); // Копируем строку в дубликат
    return dup; // Возвращаем дубликат
}