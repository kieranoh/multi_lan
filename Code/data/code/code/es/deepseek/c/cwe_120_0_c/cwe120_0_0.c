#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Constante para el mensaje base
    const char *base_message = "¡Felicidades, ";
    const char *ending = "!";
    
    // Calcular la longitud total necesaria
    int base_len = strlen(base_message);
    int ending_len = strlen(ending);
    
    // Asegurarse de que userName_size sea válido
    int actual_user_len = 0;
    if (userName != NULL && userName_size > 0) {
        // Encontrar la longitud real del nombre de usuario (hasta userName_size o hasta el primer nulo)
        for (actual_user_len = 0; actual_user_len < userName_size && userName[actual_user_len] != '\0'; actual_user_len++);
    }
    
    // Calcular la longitud total del mensaje
    int total_len_needed = base_len + actual_user_len + ending_len;
    
    // Verificar si el buffer es suficiente
    if (buffer == NULL || buffer_size <= 0) {
        return; // Buffer inválido, no hacer nada
    }
    
    // Si el buffer es demasiado pequeño, truncar el mensaje
    if (total_len_needed >= buffer_size) {
        // Calcular cuánto del nombre de usuario podemos incluir
        int available_for_user = buffer_size - base_len - ending_len - 1; // -1 para el carácter nulo
        
        if (available_for_user < 0) {
            // Ni siquiera podemos incluir el mensaje base completo
            // Copiar lo máximo posible del mensaje base
            strncpy(buffer, base_message, buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
            return;
        }
        
        // Copiar el mensaje base
        strcpy(buffer, base_message);
        
        // Copiar la parte disponible del nombre de usuario
        if (available_for_user > 0 && actual_user_len > 0) {
            strncat(buffer, userName, available_for_user);
        }
        
        // Agregar el final
        strcat(buffer, ending);
        
        // Asegurar terminación nula
        buffer[buffer_size - 1] = '\0';
    } else {
        // Buffer es suficiente para el mensaje completo
        strcpy(buffer, base_message);
        
        if (actual_user_len > 0) {
            strncat(buffer, userName, actual_user_len);
        }
        
        strcat(buffer, ending);
    }
}