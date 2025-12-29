#include <string.h>

/* src'nin içeriğini mümkün olduğunca dest'e kopyalamak için strncpy kullanın

@param dest: hedef tampon
@param dest_size: hedef tamponun boyutu
@param src: kaynak tampon
@param src_size: kaynak tamponun boyutu */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Geçersiz parametre kontrolü
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // src_size negatifse, NULL sonlandırılmış string olarak kabul et
    if (src_size < 0) {
        // strncpy kullanarak kopyala
        strncpy(dest, src, dest_size - 1);
        // strncpy null-termination garantisi vermez, bu yüzden manuel olarak ekle
        dest[dest_size - 1] = '\0';
    } else {
        // Kopyalanacak maksimum karakter sayısını belirle
        // dest_size-1 kadar kopyala (null karakter için yer bırak)
        size_t copy_size = (size_t)(dest_size - 1);
        
        // Eğer src_size daha küçükse, onu kullan
        if (src_size < dest_size - 1) {
            copy_size = (size_t)src_size;
        }
        
        // strncpy kullanarak kopyala
        strncpy(dest, src, copy_size);
        // Null-termination'ı garanti et
        dest[copy_size] = '\0';
    }
}