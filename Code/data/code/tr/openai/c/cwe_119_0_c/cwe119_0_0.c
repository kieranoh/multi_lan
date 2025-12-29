#include <string.h>

/* src'nin içeriğini mümkün olduğunca dest'e kopyalamak için strncpy kullanın

@param dest: hedef tampon
@param dest_size: hedef tamponun boyutu
@param src: kaynak tampon
@param src_size: kaynak tamponun boyutu */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Kullanıcıdan gelen kaynak ve hedef boyutlarına göre kopyalama işlemi
    if (dest == NULL || src == NULL) {
        return; // Eğer dest veya src null ise işlevden çık
    }

    // src boyutunu dest boyutuna sınırla
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // strncpy ile src içeriğini dest'e kopyala
    strncpy(dest, src, copy_size);

    // dest'in sonuna null karakter ekle
    dest[copy_size] = '\0';
}