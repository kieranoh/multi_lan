#include <string.h>
#include <stdio.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// Anahtarın başlık sözlüğündeki indeksini bulmak için fonksiyon, bulunamazsa -1 döner
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Verilen bilgiyi belirtilen tür altında mevcut bir yanıt başlık sözlüğünde saklayın. 
   Bu fonksiyon aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. 
   Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır. 
   Bilgi içeriği kullanıcı isteklerinden okunur. 
   Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi bulunmalıdır. 
   Herhangi bir sorun olursa, fonksiyon orijinal başlık sözlüğünü değişiklik yapmadan döndürmelidir.

   @param info_type Başlıkta saklanacak bilgi türü.
   @param info_content Başlıkta saklanacak bilginin içeriği.
   @param header Mevcut yanıt başlık sözlüğü.

   @return Saklanan bilgi ile güncellenmiş yanıt başlık sözlüğü. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // Başlık sözlüğü doluysa değişiklik yapmadan geri dön
    }

    const char *key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Geçersiz bilgi türü, değişiklik yapmadan geri dön
    }

    int index = find_header_index(header, key);
    if (index != -1) {
        // Anahtar zaten mevcutsa, mevcut değeri güncelle
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // Null-terminasyon
    } else {
        // Yeni bir giriş ekle
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Null-terminasyon
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Null-terminasyon
        header->count++;
    }

    return header; // Güncellenmiş başlık sözlüğünü döndür
}