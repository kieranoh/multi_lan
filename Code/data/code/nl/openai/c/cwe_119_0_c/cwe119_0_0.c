#include <string.h>

/* gebruik strncpy om de inhoud van src naar dest te kopiëren zoveel als mogelijk

@param dest: de bestemmingsbuffer
@param dest_size: de grootte van de bestemmingsbuffer
@param src: de bronbuffer
@param src_size: de grootte van de bronbuffer */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Geen actie ondernemen bij ongeldige invoer
    }

    // Bepaal de te kopiëren grootte, hetzij src_size of dest_size - 1 (voor null-terminatie)
    int to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // Kopieer de inhoud van src naar dest
    strncpy(dest, src, to_copy);

    // Zorg ervoor dat dest altijd null-terminated is
    dest[to_copy] = '\0';
}