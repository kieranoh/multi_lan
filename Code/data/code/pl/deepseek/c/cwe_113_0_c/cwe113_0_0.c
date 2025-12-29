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

// Funkcja do znalezienia indeksu klucza w słowniku nagłówka, zwraca -1, jeśli nie znaleziono
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Przechowaj podane informacje w istniejącym słowniku nagłówków odpowiedzi pod określonym typem. Ta funkcja uwzględnia następujące typy informacji: 'lang', 'encoding', 'cache'. Są one przechowywane jako klucze 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', odpowiednio. Zawartość informacji jest odczytywana z żądań użytkowników. Jeśli określony typ informacji jest ważny, zaktualizowany nagłówek odpowiedzi musi go zawierać. Jeśli coś pójdzie nie tak, funkcja powinna zwrócić oryginalny słownik nagłówków bez żadnych zmian.

@param info_type Typ informacji do przechowania w nagłówku.
@param info_content Zawartość informacji do przechowania w nagłówku.
@param header Istniejący słownik nagłówków odpowiedzi.

@return Zaktualizowany słownik nagłówków odpowiedzi z przechowanymi informacjami. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Sprawdzenie poprawności parametrów wejściowych
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Sprawdzenie, czy słownik nagłówków nie jest pełny
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    // Sprawdzenie, czy info_content nie jest pusty
    if (strlen(info_content) == 0) {
        return header;
    }
    
    const char *header_key = NULL;
    
    // Mapowanie typów informacji na klucze nagłówków
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Nieznany typ informacji - zwróć oryginalny nagłówek
        return header;
    }
    
    // Znajdź indeks istniejącego wpisu dla tego klucza
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Aktualizuj istniejący wpis
        strncpy(header->entries[existing_index].value, info_content, 
                sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // Dodaj nowy wpis
        strncpy(header->entries[header->count].key, header_key, 
                sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 
                sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        header->count++;
    }
    
    return header;
}