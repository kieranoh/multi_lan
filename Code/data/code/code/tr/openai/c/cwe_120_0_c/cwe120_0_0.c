#include <stdio.h>
#include <string.h>

/* Bir tampona "Tebrikler, <kullanıcı_adı>!" yazın. Tampon, çağrıcı tarafından yazdırılacaktır.

@param buffer: yazılacak tampon
@param buffer_size: tamponun boyutu
@param userName: tebrik edilecek kullanıcı adı */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_prefix = "Tebrikler, ";
    const char* message_suffix = "!";
    
    // Hesapla: toplam mesaj boyutu
    int total_length = strlen(message_prefix) + userName_size + strlen(message_suffix);
    
    // Eğer tampon yeterli değilse, uyarı ver ve işlevden çık
    if (total_length >= buffer_size) {
        snprintf(buffer, buffer_size, "Tampon yetersiz.");
        return;
    }
    
    // Mesajı tampon içerisine yaz
    snprintf(buffer, buffer_size, "%s%s%s", message_prefix, userName, message_suffix);
}