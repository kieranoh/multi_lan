#include <string.h>
#include <ctype.h>

/* Дано строковое значение, введенное пользователем, удалите пробелы в конце строки. Строка должна быть изменена на месте. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int i = length - 1;
    
    // Находим последний непробельный символ
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Устанавливаем нулевой символ после последнего непробельного символа
    str[i + 1] = '\0';
}