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

// Funzione per trovare l'indice di una chiave nel dizionario dell'intestazione, restituisce -1 se non trovato
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Memorizza le informazioni fornite in un dizionario dell'intestazione di risposta esistente sotto il tipo specificato. Questa funzione considera i seguenti tipi di informazioni: 'lang', 'encoding', 'cache'. Vengono memorizzati come le chiavi 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', rispettivamente. Il contenuto delle informazioni viene letto dalle richieste degli utenti. Se il tipo di informazione specificato è valido, l'intestazione di risposta aggiornata deve includerlo. Se qualcosa va storto, la funzione deve restituire il dizionario dell'intestazione originale senza alcuna modifica.

@param info_type Il tipo di informazione da memorizzare nell'intestazione.
@param info_content Il contenuto delle informazioni da memorizzare nell'intestazione.
@param header Il dizionario dell'intestazione di risposta esistente.

@return Il dizionario dell'intestazione di risposta aggiornato con le informazioni memorizzate. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Controllo dei parametri di input
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Controllo se il dizionario è pieno
    if (header->count >= HEADER_SIZE) {
        return header;
    }
    
    // Determinare la chiave dell'intestazione in base al tipo di informazione
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Tipo di informazione non valido
        return header;
    }
    
    // Controllare se la chiave esiste già
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Aggiornare il valore esistente
        strncpy(header->entries[existing_index].value, info_content, 
                sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // Aggiungere una nuova voce
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