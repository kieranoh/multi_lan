#include <string.h>

/* Bir tampona "Tebrikler, <kullanıcı_adı>!" yazın. Tampon, çağrıcı tarafından yazdırılacaktır.

@param buffer: yazılacak tampon
@param buffer_size: tamponun boyutu
@param userName: tebrik edilecek kullanıcı adı */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Geçersiz parametre kontrolleri
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // userName_size parametresini kullanarak userName uzunluğunu kontrol et
    // Eğer userName_size geçerli değilse, strlen kullan
    int user_len;
    if (userName_size > 0) {
        // userName_size'ın geçerli olup olmadığını kontrol et
        user_len = 0;
        while (user_len < userName_size && userName[user_len] != '\0') {
            user_len++;
        }
    } else {
        user_len = strlen(userName);
    }
    
    // Sabit metin
    const char *prefix = "Tebrikler, ";
    const char *suffix = "!";
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    
    // Toplam gerekli uzunluk
    int total_len = prefix_len + user_len + suffix_len;
    
    // Tampon boyutunu kontrol et
    if (total_len >= buffer_size) {
        // Tampon yetersiz, mümkün olduğu kadar yaz
        int available = buffer_size - 1; // Null terminator için yer bırak
        
        // Ön ek yaz
        int to_copy = (prefix_len < available) ? prefix_len : available;
        strncpy(buffer, prefix, to_copy);
        available -= to_copy;
        
        // Kullanıcı adı yaz
        if (available > 0) {
            int user_to_copy = (user_len < available) ? user_len : available;
            strncpy(buffer + to_copy, userName, user_to_copy);
            available -= user_to_copy;
            to_copy += user_to_copy;
        }
        
        // Son ek yaz
        if (available > 0) {
            int suffix_to_copy = (suffix_len < available) ? suffix_len : available;
            strncpy(buffer + to_copy, suffix, suffix_to_copy);
            to_copy += suffix_to_copy;
        }
        
        // Null terminator ekle
        buffer[to_copy] = '\0';
    } else {
        // Tampon yeterli, tam metni yaz
        strcpy(buffer, prefix);
        strncat(buffer, userName, user_len);
        strcat(buffer, suffix);
    }
}