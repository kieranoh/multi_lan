#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Calcular la longitud de la cadena base
    const char *prefix = "Felicitats, ";
    const char *suffix = "!";
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    
    // Calcular la longitud total necessària
    int total_len = prefix_len + userName_size + suffix_len;
    
    // Verificar que el buffer sigui suficient
    if (buffer_size <= total_len) {
        // Si el buffer és massa petit, escriure el màxim possible
        int available = buffer_size - 1; // Reservar espai per al caràcter nul
        
        if (available > 0) {
            // Copiar el prefix fins on sigui possible
            int prefix_to_copy = (prefix_len < available) ? prefix_len : available;
            strncpy(buffer, prefix, prefix_to_copy);
            available -= prefix_to_copy;
            
            // Copiar el nom d'usuari fins on sigui possible
            if (available > 0) {
                int username_to_copy = (userName_size < available) ? userName_size : available;
                strncpy(buffer + prefix_to_copy, userName, username_to_copy);
                available -= username_to_copy;
                
                // Copiar el sufix fins on sigui possible
                if (available > 0) {
                    int suffix_to_copy = (suffix_len < available) ? suffix_len : available;
                    strncpy(buffer + prefix_to_copy + username_to_copy, suffix, suffix_to_copy);
                    available -= suffix_to_copy;
                }
            }
            
            // Assegurar terminació nul·la
            buffer[buffer_size - 1] = '\0';
        } else {
            // Buffer massa petit fins i tot per al caràcter nul
            if (buffer_size > 0) {
                buffer[0] = '\0';
            }
        }
    } else {
        // Buffer suficient, copiar tot
        strcpy(buffer, prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, suffix);
    }
}