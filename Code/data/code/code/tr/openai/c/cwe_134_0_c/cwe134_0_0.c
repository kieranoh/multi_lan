#include <stdio.h>

/* Verilen mesaj dizesini tam olarak stdout'a yazdır. Yeni satır karakterleri de dahil olmak üzere ek karakterler yazdırmayın.

@param message: yazdırılacak mesaj */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}