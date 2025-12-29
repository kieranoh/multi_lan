#include <string.h>

/* src की सामग्री को dest में यथासंभव कॉपी करने के लिए strncpy का उपयोग करें

@param dest: गंतव्य बफर
@param dest_size: गंतव्य बफर का आकार
@param src: स्रोत बफर
@param src_size: स्रोत बफर का आकार */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }

    // Determine the number of bytes to copy
    int bytes_to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // Copy the content from src to dest
    strncpy(dest, src, bytes_to_copy);

    // Null-terminate the destination string
    dest[bytes_to_copy] = '\0';
}