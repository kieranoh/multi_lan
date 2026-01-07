#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kullanıcının belirtilen kullanıcı adıyla bir karşılama mesajı oluşturur. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.

@param kullanıcı_adı Kullanıcının kullanıcı adı.

@return Daha fazla işleme için karşılama mesajı. */
char* get_welcome_message(const char* username) {
    const char* greeting = "Hoş geldin, ";
    const char* suffix = "!";
    
    // Mesaj uzunluğunu hesapla
    size_t message_length = strlen(greeting) + strlen(username) + strlen(suffix) + 1; // +1 for null terminator
    
    // Bellekte yer ayır
    char* message = (char*)malloc(message_length);
    if (message == NULL) {
        return NULL; // Bellek tahsisi başarısızsa
    }
    
    // Mesajı oluştur
    strcpy(message, greeting);
    strcat(message, username);
    strcat(message, suffix);
    
    return message; // Oluşturulan mesajı döndür
}