#include <stdlib.h>
#include <string.h>

/* Dla danego ciągu zwróć duplikat tego ciągu. Duplikat powinien być przydzielony na stercie, a wywołujący jest odpowiedzialny za jego zwolnienie.

@param str: ciąg do duplikacji
@return duplikat ciągu */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* duplicate = (char*)malloc(len + 1); // +1 for the null terminator
    if (duplicate == NULL) {
        return NULL; // Allocation failed
    }
    
    strcpy(duplicate, str);
    return duplicate;
}