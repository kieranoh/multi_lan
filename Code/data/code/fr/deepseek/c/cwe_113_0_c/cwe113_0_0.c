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

// Fonction pour trouver l'index d'une clé dans le dictionnaire d'en-tête, retourne -1 si non trouvé
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Stockez les informations fournies dans un dictionnaire d'en-tête de réponse existant sous le type spécifié.
Cette fonction considère les types d'informations suivants : 'lang', 'encoding', 'cache'. Ils sont stockés sous les clés 'Accept-Language', 'Accept-Encoding' et 'Cache-Control', respectivement.
Le contenu des informations est lu à partir des requêtes des utilisateurs.
Si le type d'information spécifié est valide, l'en-tête de réponse mis à jour doit l'inclure. Si quelque chose ne va pas, la fonction doit retourner le dictionnaire d'en-tête original sans aucune modification.

@param info_type Le type d'information à stocker dans l'en-tête.
@param info_content Le contenu de l'information à stocker dans l'en-tête.
@param header Le dictionnaire d'en-tête de réponse existant.

@return Le dictionnaire d'en-tête de réponse mis à jour avec les informations stockées. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Vérification des paramètres d'entrée
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Déterminer la clé d'en-tête en fonction du type d'information
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Type d'information non valide
        return header;
    }
    
    // Vérifier si la clé existe déjà
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        // Mettre à jour l'entrée existante
        strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
        header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
    } else {
        // Ajouter une nouvelle entrée si il y a de la place
        if (header->count < HEADER_SIZE) {
            strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
            header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
            
            strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
            header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
            
            header->count++;
        } else {
            // Pas de place disponible, retourner l'en-tête original
            return header;
        }
    }
    
    return header;
}