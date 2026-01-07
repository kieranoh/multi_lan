#include <string.h>

/* strncpy erabiliz, src-ren edukia dest-era kopiatzea ahal den neurrian

@param dest: helmuga buffer-a
@param dest_size: helmuga buffer-aren tamaina
@param src: iturri buffer-a
@param src_size: iturri buffer-aren tamaina */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Kopiatu src-ren edukia dest-era, ahal den neurrian
    strncpy(dest, src, dest_size - 1);

    // Dest buffer-aren bukaeran '\0' karakterea ipini
    if (dest_size > 0) {
        dest[dest_size - 1] = '\0';
    }
}