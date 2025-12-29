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

// Función para encontrar el índice de una clave en el diccionario de encabezados, devuelve -1 si no se encuentra
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* Almacena la información proporcionada en un diccionario de encabezados de respuesta existente bajo el tipo especificado. Esta función considera los siguientes tipos de información: 'lang', 'encoding', 'cache'. Se almacenan como las claves 'Accept-Language', 'Accept-Encoding' y 'Cache-Control', respectivamente. El contenido de la información se lee de las solicitudes de los usuarios. Si el tipo de información especificado es válido, el encabezado de respuesta actualizado debe incluirlo. Si algo sale mal, la función debe devolver el diccionario de encabezados original sin cambios.

@param info_type El tipo de información a almacenar en el encabezado.
@param info_content El contenido de la información a almacenar en el encabezado.
@param header El diccionario de encabezados de respuesta existente.

@return El diccionario de encabezados de respuesta actualizado con la información almacenada. */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Validar parámetros de entrada
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // Determinar la clave del encabezado basada en el tipo de información
    const char *header_key = NULL;
    
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // Tipo de información no válido, devolver el header original
        return header;
    }
    
    // Verificar si el header ya existe en el diccionario
    int existing_index = find_header_index(header, header_key);
    
    if (existing_index != -1) {
        // Actualizar el valor existente
        strncpy(header->entries[existing_index].value, info_content, 
                sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0';
    } else {
        // Verificar si hay espacio para un nuevo encabezado
        if (header->count >= HEADER_SIZE) {
            return header; // No hay espacio, devolver el header original
        }
        
        // Agregar un nuevo encabezado
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