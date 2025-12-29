#include <string.h>
#include <stdlib.h>

HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Vytvoření kopie původního header pro případ chyby
    HeaderDict *original_header = malloc(sizeof(HeaderDict));
    if (original_header == NULL) {
        return header;
    }
    
    // Kopírování původního stavu
    memcpy(original_header, header, sizeof(HeaderDict));
    
    // Určení klíče na základě typu informace
    const char *key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        // Neplatný typ informace - vracíme původní header
        free(original_header);
        return header;
    }
    
    // Kontrola platnosti info_content
    if (info_content == NULL || strlen(info_content) == 0) {
        free(original_header);
        return header;
    }
    
    // Kontrola, zda klíč již existuje
    int index = find_header_index(header, key);
    
    if (index != -1) {
        // Aktualizace existující položky
        if (strlen(info_content) < sizeof(header->entries[index].value)) {
            strcpy(header->entries[index].value, info_content);
        } else {
            // Obsah je příliš dlouhý - vracíme původní header
            HeaderDict *temp = header;
            memcpy(header, original_header, sizeof(HeaderDict));
            free(original_header);
            return temp;
        }
    } else {
        // Přidání nové položky
        if (header->count >= HEADER_SIZE) {
            // Slovník je plný - vracíme původní header
            free(original_header);
            return header;
        }
        
        // Kontrola délky klíče
        if (strlen(key) >= sizeof(header->entries[0].key)) {
            free(original_header);
            return header;
        }
        
        // Kontrola délky hodnoty
        if (strlen(info_content) >= sizeof(header->entries[0].value)) {
            free(original_header);
            return header;
        }
        
        // Přidání nové položky
        strcpy(header->entries[header->count].key, key);
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    }
    
    // Úspěšné dokončení - uvolníme kopii a vrátíme aktualizovaný header
    free(original_header);
    return header;
}