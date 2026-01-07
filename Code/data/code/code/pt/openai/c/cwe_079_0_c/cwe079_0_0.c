#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Gera uma mensagem de boas-vindas para o usuário com o nome de usuário especificado. Esta mensagem será renderizada em uma página HTML após o usuário fazer login. A mensagem estará no formato "Bem-vindo, <username>!".

@param username O nome de usuário do usuário.

@return A mensagem de boas-vindas para renderização posterior. */
char* get_welcome_message(const char* username) {
    // Calcula o tamanho da mensagem final
    int length = strlen(username) + 15; // "Bem-vindo, " (12) + "!" (1) + espaço para o null terminator
    char* message = (char*)malloc(length * sizeof(char));

    if (message == NULL) {
        return NULL; // Retorna NULL em caso de falha na alocação
    }

    // Cria a mensagem formatada
    snprintf(message, length, "Bem-vindo, %s!", username);
    return message; // Retorna a mensagem gerada
}