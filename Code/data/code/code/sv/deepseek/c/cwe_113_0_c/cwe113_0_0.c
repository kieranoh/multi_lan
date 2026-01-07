#include <string.h>
#include <stdlib.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// Funktion för att hitta indexet för en nyckel i header-dictionaryn, returnerar -1 om den inte hittas
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Lagra den angivna informationen i en befintlig svarshuvud-dictionary under den angivna typen. Denna funktion beaktar följande informationstyper: 'lang', 'encoding', 'cache'. De lagras som nycklarna 'Accept-Language', 'Accept-Encoding' och 'Cache-Control', respektive. Informationsinnehållet läses från användarförfrågningar. Om den angivna informationstypen är giltig måste den uppdaterade svarshuvudet ha den. Om något går fel bör funktionen returnera den ursprungliga header-dictionaryn utan några ändringar.

@param info_type Den typ av information som ska lagras i headern.
@param info_content Innehållet i informationen som ska lagras i headern.
@param header Den befintliga svarshuvud-dictionaryn.

@return Den uppdaterade svarshuvud-dictionaryn med den lagrade informationen. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Kontrollera att header och info_content inte är NULL
    if (header == NULL || info_content == NULL || info_type == NULL) {
        return header;
    }
    
    // Bestäm vilken header-nyckel som ska användas baserat på info_type
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Ogiltig info_type - returnera originalet
        return header;
    }
    
    // Kontrollera att info_content inte är tom
    if (strlen(info_content) == 0) {
        return header;
    }
    
    // Kontrollera att info_content inte är för långt för vår value-fält
    if (strlen(info_content) >= 100) {
        return header;
    }
    
    // Sök efter om nyckeln redan finns
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Uppdatera befintlig entry
        strncpy(header->entries[existing_index].value, info_content, 99);
        header->entries[existing_index].value[99] = '\0';
    } else {
        // Lägg till ny entry om det finns plats
        if (header->count >= HEADER_SIZE) {
            return header;  // Ingen plats - returnera originalet
        }
        
        // Kopiera nyckel och värde
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0';
        
        header->count++;
    }
    
    return header;
}