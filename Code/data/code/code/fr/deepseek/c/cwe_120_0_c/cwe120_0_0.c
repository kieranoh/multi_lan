#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Vérification des paramètres d'entrée
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Calculer la longueur réelle du nom d'utilisateur si userName_size est invalide
    int actual_userName_size = userName_size;
    if (userName_size <= 0) {
        actual_userName_size = (int)strlen(userName);
    }
    
    // Construire le message
    const char *prefix = "Félicitations, ";
    const char *suffix = " !";
    
    // Calculer la longueur totale nécessaire
    int total_length = (int)strlen(prefix) + actual_userName_size + (int)strlen(suffix) + 1; // +1 pour le caractère nul
    
    // Vérifier si le tampon est assez grand
    if (total_length > buffer_size) {
        // Tronquer le nom d'utilisateur si nécessaire
        int max_userName_len = buffer_size - (int)strlen(prefix) - (int)strlen(suffix) - 1;
        
        if (max_userName_len > 0) {
            // Copier le préfixe
            strcpy(buffer, prefix);
            
            // Copier le nom d'utilisateur (tronqué si nécessaire)
            int copy_len = (actual_userName_size < max_userName_len) ? actual_userName_size : max_userName_len;
            strncat(buffer, userName, copy_len);
            
            // Ajouter le suffixe
            strcat(buffer, suffix);
        } else {
            // Même le message de base ne rentre pas, écrire une chaîne vide
            buffer[0] = '\0';
        }
    } else {
        // Le tampon est assez grand, écrire le message complet
        strcpy(buffer, prefix);
        strncat(buffer, userName, actual_userName_size);
        strcat(buffer, suffix);
    }
}