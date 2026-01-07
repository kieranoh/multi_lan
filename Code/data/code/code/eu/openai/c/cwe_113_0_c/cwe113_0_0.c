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

/* Emandako informazioa lehendik dagoen erantzunaren goiburuko hitzategian gorde zehaztutako motaren arabera.
Funtzio honek informazio mota hauek kontuan hartzen ditu: 'lang', 'encoding', 'cache'. Hori 'Accept-Language', 'Accept-Encoding' eta 'Cache-Control' gako gisa gordetzen da, hurrenez hurren.
Informazio edukiak erabiltzaileen eskaeretatik irakurtzen dira.
Zehaztutako informazio mota balidua bada, eguneratutako erantzun goiburua horrekin izan behar du. Edozein arazo izanez gero, funtzioak jatorrizko goiburuko hitzategia itzuli behar du aldaketarik gabe.

@param info_type Goiburuan gorde beharreko informazioaren mota.
@param info_content Goiburuan gorde beharreko informazioaren eduki.
@param header Lehendik dagoen erantzun goiburuko hitzategia.

@return Gorde den informazioarekin eguneratutako erantzun goiburuko hitzategia. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    if (header == NULL || info_type == NULL || info_content == NULL) {
        return header; // Itzuli jatorrizko goiburua, balio baldin badago
    }

    int index = -1;

    // Emandako info_type-a irakurri eta egiaztatu
    if (strcmp(info_type, "lang") == 0) {
        index = find_header_index(header, "Accept-Language");
    } else if (strcmp(info_type, "encoding") == 0) {
        index = find_header_index(header, "Accept-Encoding");
    } else if (strcmp(info_type, "cache") == 0) {
        index = find_header_index(header, "Cache-Control");
    } 

    // Baldintza egokia bada
    if (index != -1) {
        // Gakoa aurkitu da; eguneratu balioa
        strncpy(header->entries[index].value, info_content, 100);
    } else if (header->count < HEADER_SIZE) {
        // Gakoa ez da aurkitu; berri bat gehitu
        if (strcmp(info_type, "lang") == 0) {
            strncpy(header->entries[header->count].key, "Accept-Language", 50);
        } else if (strcmp(info_type, "encoding") == 0) {
            strncpy(header->entries[header->count].key, "Accept-Encoding", 50);
        } else if (strcmp(info_type, "cache") == 0) {
            strncpy(header->entries[header->count].key, "Cache-Control", 50);
        }
        strncpy(header->entries[header->count].value, info_content, 100);
        header->count++;
    }

    return header; // Itzuli eguneratutako goiburua
}