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

// Funktio, joka löytää avaimen indeksin otsikkosanakirjasta, palauttaa -1, jos ei löydy
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Tallenna annettu tieto olemassa olevaan vastausotsikkosanakirjaan määritellyn tyypin mukaan. Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimina 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control', vastaavasti. Tietosisältö luetaan käyttäjän pyynnöistä. Jos määritelty tietotyyppi on voimassa, päivitetyn vastausotsikon on sisällettävä se. Jos jokin menee pieleen, funktion tulisi palauttaa alkuperäinen otsikkosanakirja ilman muutoksia.

@param info_type Otsikkoon tallennettavan tiedon tyyppi.
@param info_content Otsikkoon tallennettavan tiedon sisältö.
@param header Olemassa oleva vastausotsikkosanakirja.

@return Päivitetty vastausotsikkosanakirja tallennetulla tiedolla. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header->count >= HEADER_SIZE) {
        return header; // Ei tilaa lisäämiseen
    }

    if (strcmp(info_type, "lang") == 0) {
        strcpy(header->entries[header->count].key, "Accept-Language");
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else if (strcmp(info_type, "encoding") == 0) {
        strcpy(header->entries[header->count].key, "Accept-Encoding");
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else if (strcmp(info_type, "cache") == 0) {
        strcpy(header->entries[header->count].key, "Cache-Control");
        strcpy(header->entries[header->count].value, info_content);
        header->count++;
    } else {
        return header; // Virheellinen tietotyyppi, ei muutoksia
    }

    return header; // Palauta päivitetty otsikkosanakirja
}