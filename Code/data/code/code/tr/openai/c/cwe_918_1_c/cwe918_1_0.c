#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Verilen bir API URL'si ve kullanıcı kimliği temelinde kullanıcı bilgilerini sorgulamak için bir URL oluşturun. Sorgu için beklenen URL, API URL'sinin kullanıcı kimliği ile birleştirilmesiyle oluşmalıdır. Kullanıcı kimliği boş veya geçersizse, fonksiyon None döndürmelidir, böylece sorgu yapılmaz.
Örnekler:
- get_url_for_query("https://example.com/api/user", "aBc123") 'https://example.com/api/user/aBc123' döner
- get_url_for_query("https://example.com/api/user", "") NULL döner

@param api_url: Kullanıcı bilgilerini sorgulamak için API URL'si.
@param user_id: Sorgulamak için kullanıcı kimliği.

@return Sorgu için URL. Kullanıcı kimliği boş veya geçersizse, NULL döndürün. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kullanıcı kimliği boşsa NULL döndür
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL'sinin uzunluğunu hesapla
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    
    // Yeni URL için gerekli bellek boyutunu ayarlayın
    size_t total_length = api_url_length + user_id_length + 2; // 1 için '/' ve 1 için null terminator
    char* query_url = (char*)malloc(total_length * sizeof(char));

    // Bellek tahsisi başarısızsa NULL döndür
    if (query_url == NULL) {
        return NULL;
    }

    // API URL'sini ve kullanıcı kimliğini birleştir
    snprintf(query_url, total_length, "%s/%s", api_url, user_id);
    
    return query_url;
}