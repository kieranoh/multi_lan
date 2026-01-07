#include <stdlib.h>
#include <string.h>

/* Zadaný řetězec, vraťte duplikát řetězce. Duplikát by měl být alokován na haldě a volající je zodpovědný za jeho uvolnění.

@param str: řetězec k duplikaci
@return duplikát řetězce */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Ošetření NULL vstupu
    }
    
    size_t len = strlen(str); // Získání délky řetězce
    char* dup = (char*)malloc(len + 1); // Alokace paměti na duplikát (+1 pro nulový terminátor)
    
    if (dup == NULL) {
        return NULL; // Ošetření neúspěšné alokace
    }
    
    strcpy(dup, str); // Zkopírování původního řetězce do duplikátu
    return dup; // Vrátí duplikovaný řetězec
}