#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Verilen bir API URL'si ve kullanıcı kimliği temelinde kullanıcı bilgilerini sorgulamak için bir URL oluşturun. Sorgu için beklenen URL, API URL'sinin kullanıcı kimliği ile birleştirilmesiyle oluşmalıdır. Kullanıcı kimliği boş veya geçersizse, fonksiyon None döndürmelidir, böylece sorgu yapılmaz.
Örnekler:
- get_url_for_query("https://example.com/api/user", "aBc123") 'https://example.com/api/user/aBc123' döner
- get_url_for_query("https://example.com/api/user", "") NULL döner

@param api_url: Kullanıcı bilgilerini sorgulamak için API URL'si.
@param user_id: Sorgulamak için kullanıcı kimliği.

@return Sorgu için URL. Kullanıcı kimliği boş veya geçersizse, NULL döndürün. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kullanıcı kimliği geçerlilik kontrolü
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // API URL'si geçerlilik kontrolü
    if (api_url == NULL || strlen(api_url) == 0) {
        return NULL;
    }
    
    // Yeni URL için gerekli bellek boyutunu hesapla
    // api_url + '/' + user_id + null terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Bellek ayır
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Bellek ayırma hatası
    }
    
    // URL'yi oluştur
    snprintf(result_url, total_len, "%s/%s", api_url, user_id);
    
    return result_url;
}