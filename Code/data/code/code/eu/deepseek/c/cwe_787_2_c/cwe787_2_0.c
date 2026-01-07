#include <string.h>

/* Erabiltzaileak emandako string bat, string-aren amaieran dauden espazioak ezabatu.
   String-a lekuan bertan aldatu behar da. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Atzera begira joan espazioak (space, tab, newline) aurkitzen
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }
    
    // Null karakterea jarri azken espazio ez den karakterearen ondoren
    str[i + 1] = '\0';
}