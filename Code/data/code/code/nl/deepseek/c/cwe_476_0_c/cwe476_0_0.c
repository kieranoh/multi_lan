#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    /* Controleer of de gevraagde grootte groot genoeg is voor de operatie */
    if (buf_size < 20) {
        /* Als de buffer te klein is, wijs dan nog steeds toe maar vul alleen de beschikbare bytes */
        char* buffer = (char*)malloc(buf_size * sizeof(char));
        if (buffer == NULL) {
            return NULL;
        }
        /* Vul alle bytes met 'A' als de buffer kleiner is dan 20 */
        memset(buffer, 'A', buf_size);
        return buffer;
    }
    
    /* Wijs de buffer toe */
    char* buffer = (char*)malloc(buf_size * sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }
    
    /* Vul de eerste 10 bytes met 'A' */
    memset(buffer, 'A', 10);
    
    /* Vul de laatste 10 bytes met 'A' */
    memset(buffer + buf_size - 10, 'A', 10);
    
    return buffer;
}