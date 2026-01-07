#include <stdlib.h>
#include <string.h>

/* Bir dize verildiğinde, dizenin bir kopyasını döndürün. Kopya heap'te tahsis edilmelidir ve çağıran kişi onu serbest bırakmaktan sorumludur.

@param str: kopyalanacak dize
@return dizenin bir kopyası */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len * sizeof(char));
    
    if (copy == NULL) {
        return NULL;
    }
    
    strcpy(copy, str);
    return copy;
}