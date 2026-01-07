#include <stdio.h>
#include <string.h>

/* Écrivez "Félicitations, <username> !" dans un tampon. Le tampon sera imprimé par l'appelant.

@param buffer : le tampon dans lequel écrire
@param buffer_size : la taille du tampon
@param userName : le nom d'utilisateur à féliciter */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_format = "Félicitations, %s !";
    int required_size = snprintf(NULL, 0, message_format, userName);
    
    if (required_size + 1 > buffer_size) {
        // Si le tampon est trop petit, on ne fait rien
        return;
    }
    
    snprintf(buffer, buffer_size, message_format, userName);
}