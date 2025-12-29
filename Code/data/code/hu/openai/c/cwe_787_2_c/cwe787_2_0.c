#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Egy felhasználó által megadott karakterláncból távolítsa el a végső szóközöket. A karakterláncot helyben kell módosítani. */
void trim_spaces(char* str) {
    if (str == NULL) return;

    int len = strlen(str);
    int i;

    // Végigmegyünk a karakterláncon visszafelé, hogy megtaláljuk az utolsó nem szóköz karaktert
    for (i = len - 1; i >= 0; i--) {
        if (!isspace((unsigned char)str[i])) {
            break;
        }
    }

    // Az utolsó nem szóköz karakter után mindent szóközzé kell módosítani
    str[i + 1] = '\0';
}