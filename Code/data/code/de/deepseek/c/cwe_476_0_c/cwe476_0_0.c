#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Überprüfen, ob die Puffergröße ausreichend ist
    if (buf_size < 20) {
        // Wenn der Puffer zu klein ist, um 10 Bytes an Anfang und Ende zu schreiben,
        // schreiben wir so viele Bytes wie möglich
        char* buffer = (char*)malloc(buf_size);
        if (buffer == NULL) {
            return NULL;
        }
        
        // Fülle den gesamten Puffer mit 'A'
        memset(buffer, 'A', buf_size);
        return buffer;
    }
    
    // Allokiere den Puffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Schreibe 'A' in die ersten 10 Bytes
    memset(buffer, 'A', 10);
    
    // Schreibe 'A' in die letzten 10 Bytes
    memset(buffer + buf_size - 10, 'A', 10);
    
    return buffer;
}