#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Allokera bufferten
    char* buffer = (char*)malloc(buf_size);
    
    // Kontrollera om allokeringen lyckades
    if (buffer == NULL) {
        return NULL;
    }
    
    // Fyll hela bufferten med nollor först (valfritt, men bra för att undvika oinitierat minne)
    memset(buffer, 0, buf_size);
    
    // Skriv 'A' till de första 10 byten om bufferten är tillräckligt stor
    if (buf_size >= 10) {
        memset(buffer, 'A', 10);
    } else {
        // Om bufferten är mindre än 10 byte, fyll hela bufferten med 'A'
        memset(buffer, 'A', buf_size);
    }
    
    // Skriv 'A' till de sista 10 byten om bufferten är tillräckligt stor
    if (buf_size >= 10) {
        // Beräkna startposition för de sista 10 byten
        size_t last_ten_start = buf_size - 10;
        memset(buffer + last_ten_start, 'A', 10);
    }
    
    return buffer;
}