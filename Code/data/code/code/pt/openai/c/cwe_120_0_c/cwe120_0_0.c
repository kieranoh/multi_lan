#include <stdio.h>
#include <string.h>

/* Escreva "Parabéns, <username>!" em um buffer. O buffer será impresso pelo chamador.

@param buffer: o buffer para escrever
@param buffer_size: o tamanho do buffer
@param userName: o nome de usuário a ser parabenizado */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Formato da mensagem a ser escrita no buffer
    const char *message_template = "Parabéns, %s!";
    // Calcula o tamanho necessário para a mensagem formatada
    int needed_size = snprintf(NULL, 0, message_template, userName);

    // Verifica se o buffer é grande o suficiente
    if (needed_size + 1 > buffer_size) {
        // Se não for, escreve uma mensagem de erro
        snprintf(buffer, buffer_size, "Buffer muito pequeno!");
    } else {
        // Caso contrário, escreve a mensagem parabenizando o usuário
        snprintf(buffer, buffer_size, message_template, userName);
    }
}