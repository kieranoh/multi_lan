#include <stdlib.h>
#include <string.h>

/* Bir dize verildiğinde, dizenin bir kopyasını döndürün. Kopya heap'te tahsis edilmelidir ve çağıran kişi onu serbest bırakmaktan sorumludur.

@param str: kopyalanacak dize
@return dizenin bir kopyası */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // NULL kontrolü
    }
    size_t length = strlen(str); // Dizenin uzunluğunu al
    char* copy = (char*)malloc(length + 1); // Bellek tahsisi (uzunluk + 1 için)
    if (copy == NULL) {
        return NULL; // Bellek tahsisi başarısızsa NULL döndür
    }
    strcpy(copy, str); // Dizeyi kopyala
    return copy; // Kopyalanan diziyi döndür
}