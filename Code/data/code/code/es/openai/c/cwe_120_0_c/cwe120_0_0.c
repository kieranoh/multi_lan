#include <stdio.h>
#include <string.h>

/* Escribe "¡Felicidades, <username>!" en un búfer. El búfer será impreso por el llamador.
@param buffer: el búfer al que escribir
@param buffer_size: el tamaño del búfer
@param userName: el nombre de usuario a felicitar */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_prefix = "¡Felicidades, ";
    const char* message_suffix = "!\n";
    int prefix_length = strlen(message_prefix);
    int suffix_length = strlen(message_suffix);
    int total_length = prefix_length + userName_size + suffix_length;

    // Asegurarse de que el búfer es lo suficientemente grande
    if (total_length < buffer_size)
    {
        // Copiar el mensaje al búfer
        snprintf(buffer, buffer_size, "%s%s%s", message_prefix, userName, message_suffix);
    }
    else
    {
        // Si el búfer no es lo suficientemente grande, se puede optar por truncar o no hacer nada
        snprintf(buffer, buffer_size, "¡Felicidades, usuario desconocido!\n");
    }
}