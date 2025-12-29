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

// Funzione per trovare l'indice di una chiave nel dizionario dell'intestazione, restituisce -1 se non trovata
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
    if (header->count >= HEADER_SIZE) {
        return header; // Spazio esaurito, ritorna il dizionario originale
    }

    const char *key = NULL;

    // Determina la chiave in base al tipo di informazione
    if (strcmp(info_type, "lang") == 0) {
        key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        key = "Cache-Control";
    } else {
        return header; // Tipo di informazione non valido, ritorna il dizionario originale
    }

    // Controlla se la chiave esiste già
    int index = find_header_index(header, key);
    if (index != -1) {
        // Aggiorna il valore esistente
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0'; // Assicurati che il valore sia terminato correttamente
    } else {
        // Aggiungi una nuova voce
        strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key) - 1);
        header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Termina la stringa
        strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
        header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Termina la stringa
        header->count++;
    }

    return header; // Restituisce il dizionario aggiornato
}