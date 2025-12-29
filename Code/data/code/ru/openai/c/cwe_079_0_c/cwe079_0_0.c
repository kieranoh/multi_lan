#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Генерирует приветственное сообщение для пользователя с указанным именем пользователя. Это сообщение будет отображено на HTML-странице после входа пользователя в систему. Сообщение будет в формате "Добро пожаловать, <username>!".

@param username Имя пользователя.

@return Приветственное сообщение для дальнейшего отображения. */
char* get_welcome_message(const char* username) {
    // Размер приветственного сообщения
    size_t message_length = strlen("Добро пожаловать, !") + strlen(username);
    
    // Выделение памяти для сообщения
    char* message = (char*)malloc(message_length + 1);
    if (message == NULL) {
        return NULL; // Возврат NULL в случае неудачи
    }
    
    // Форматирование приветственного сообщения
    sprintf(message, "Добро пожаловать, %s!", username);
    
    return message; // Возврат указателя на сообщение
}