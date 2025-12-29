#include <string.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Maak een lokale kopie van de header om te kunnen terugvallen op origineel bij fouten
    static HeaderDict original_header;
    original_header = *header;
    
    // Bepaal de juiste header key op basis van info_type
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Ongeldig info_type, retourneer originele header
        return header;
    }
    
    // Controleer of info_content geldig is (niet NULL en niet leeg)
    if (info_content == NULL || strlen(info_content) == 0) {
        return header;
    }
    
    // Zoek of de header key al bestaat
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        // Update bestaande entry
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
    } else {
        // Voeg nieuwe entry toe als er ruimte is
        if (header->count >= HEADER_SIZE) {
            // Geen ruimte meer, retourneer originele header
            *header = original_header;
            return header;
        }
        
        // Kopieer de key
        strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        // Kopieer de value
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        // Verhoog de count
        header->count++;
    }
    
    return header;
}