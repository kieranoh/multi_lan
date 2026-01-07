#include <string.h>
#include <ctype.h>

/* Egy felhasználó által megadott karakterláncból távolítsa el a végső szóközöket. A karakterláncot helyben kell módosítani. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int i = length - 1;
    
    // Keressük az utolsó nem szóköz karaktert
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Ha az egész string szóköz volt, vagy üres string
    if (i < 0) {
        str[0] = '\0';
    } else {
        // A következő karaktert nullával helyettesítjük
        str[i + 1] = '\0';
    }
}