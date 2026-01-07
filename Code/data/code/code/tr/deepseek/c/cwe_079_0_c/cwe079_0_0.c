#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Kullanıcının belirtilen kullanıcı adıyla bir karşılama mesajı oluşturur. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.

@param kullanıcı_adı Kullanıcının kullanıcı adı.

@return Daha fazla işleme için karşılama mesajı. */
char* get_welcome_message(const char* username) {
    // Sabit mesaj önekini tanımla
    const char* prefix = "Hoş geldin, ";
    const char* suffix = "!";
    
    // Geçersiz giriş kontrolü
    if (username == NULL) {
        // Boş kullanıcı adı için varsayılan mesaj döndür
        char* default_message = (char*)malloc(15 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Hoş geldin, !");
        }
        return default_message;
    }
    
    // Gerekli bellek miktarını hesapla: önek + kullanıcı adı + sonek + null karakter
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    
    // Toplam uzunluğu hesapla
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 for null terminator
    
    // Bellek tahsis et
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    
    // Bellek tahsis hatası kontrolü
    if (welcome_message == NULL) {
        return NULL;
    }
    
    // Mesajı oluştur
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}