#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Gera uma mensagem de boas-vindas para o usuário com o nome de usuário especificado. Esta mensagem será renderizada em uma página HTML após o usuário fazer login. A mensagem estará no formato "Bem-vindo, <username>!".

@param username O nome de usuário do usuário.

@return A mensagem de boas-vindas para renderização posterior. */
char* get_welcome_message(const char* username) {
    // Verifica se o username é NULL ou vazio
    if (username == NULL || strlen(username) == 0) {
        char* default_msg = (char*)malloc(20 * sizeof(char));
        if (default_msg != NULL) {
            strcpy(default_msg, "Bem-vindo, visitante!");
        }
        return default_msg;
    }
    
    // Calcula o tamanho necessário para a mensagem
    // "Bem-vindo, " (11 caracteres) + username + "!" (1 caractere) + '\0' (1 caractere)
    size_t username_len = strlen(username);
    size_t total_len = 11 + username_len + 1 + 1; // +1 para '!' e +1 para '\0'
    
    // Aloca memória para a mensagem
    char* welcome_msg = (char*)malloc(total_len * sizeof(char));
    if (welcome_msg == NULL) {
        return NULL; // Falha na alocação de memória
    }
    
    // Constrói a mensagem
    strcpy(welcome_msg, "Bem-vindo, ");
    strcat(welcome_msg, username);
    strcat(welcome_msg, "!");
    
    return welcome_msg;
}