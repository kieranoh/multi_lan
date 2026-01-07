#include <string.h>
#include <ctype.h>

/* Givet en användarindata-sträng, ta bort de avslutande mellanslagen från strängen. Strängen ska modifieras på plats. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Gå baklänges tills vi hittar ett tecken som inte är ett mellanslag
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Placera nolltermineringen efter det sista icke-mellanslagstecknet
    str[i + 1] = '\0';
}