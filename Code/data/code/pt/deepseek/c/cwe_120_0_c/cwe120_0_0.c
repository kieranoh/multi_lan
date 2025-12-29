#include <string.h>
#include <stdio.h>

/* Escreva "Parabéns, <username>!" em um buffer. O buffer será impresso pelo chamador.

@param buffer: o buffer para escrever
@param buffer_size: o tamanho do buffer
@param userName: o nome de usuário a ser parabenizado */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Verificar parâmetros de entrada
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Calcular o comprimento do nome de usuário (usar userName_size se fornecido, senão usar strlen)
    int name_len;
    if (userName_size > 0) {
        // Usar o tamanho fornecido, mas garantir que não exceda o comprimento real da string
        name_len = userName_size;
        // Encontrar o comprimento real se userName_size for muito grande
        for (int i = 0; i < userName_size; i++) {
            if (userName[i] == '\0') {
                name_len = i;
                break;
            }
        }
    } else {
        // Se userName_size for 0 ou negativo, usar strlen
        name_len = (int)strlen(userName);
    }
    
    // String base "Parabéns, !" tem 12 caracteres (11 + 1 para o nulo)
    const char *prefix = "Parabéns, ";
    const char *suffix = "!";
    int prefix_len = (int)strlen(prefix);
    int suffix_len = (int)strlen(suffix);
    
    // Calcular comprimento total necessário
    int total_len = prefix_len + name_len + suffix_len;
    
    // Verificar se o buffer é grande o suficiente
    if (total_len >= buffer_size) {
        // Buffer muito pequeno, truncar ou retornar string vazia
        buffer[0] = '\0';
        return;
    }
    
    // Copiar o prefixo
    strcpy(buffer, prefix);
    
    // Copiar o nome de usuário
    strncpy(buffer + prefix_len, userName, name_len);
    buffer[prefix_len + name_len] = '\0'; // Garantir terminação nula
    
    // Adicionar o sufixo
    strcat(buffer, suffix);
}