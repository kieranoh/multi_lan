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

// Funció per trobar l'índex d'una clau al diccionari d'encapçalament, retorna -1 si no es troba
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Emmagatzema la informació proporcionada en un diccionari d'encapçalament de resposta existent sota el tipus especificat. Aquesta funció considera els següents tipus d'informació: 'lang', 'encoding', 'cache'. S'emmagatzemen com les claus 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', respectivament. El contingut de la informació es llegeix de les sol·licituds d'usuari. Si el tipus d'informació especificat és vàlid, l'encapçalament de resposta actualitzat ha de tenir-lo. Si alguna cosa va malament, la funció ha de retornar el diccionari d'encapçalament original sense cap canvi.

@param info_type El tipus d'informació a emmagatzemar a l'encapçalament.
@param info_content El contingut de la informació a emmagatzemar a l'encapçalament.
@param header El diccionari d'encapçalament de resposta existent.

@return El diccionari d'encapçalament de resposta actualitzat amb la informació emmagatzemada. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Verificar punteros nulos
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Determinar la clau de l'encapçalament basada en el tipus d'informació
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Tipus d'informació no vàlid, retornar original sense canvis
        return header;
    }
    
    // Verificar que el contingut no estigui buit
    if (strlen(info_content) == 0) {
        return header;
    }
    
    // Buscar si la clau ja existeix
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Actualitzar el valor existent
        strncpy(header->entries[existing_index].value, info_content, sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // Afegir nova entrada si hi ha espai
        if (header->count >= HEADER_SIZE) {
            // No hi ha espai, retornar original sense canvis
            return header;
        }
        
        // Copiar la clau i el valor
        strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
        
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
        
        header->count++;
    }
    
    return header;
}