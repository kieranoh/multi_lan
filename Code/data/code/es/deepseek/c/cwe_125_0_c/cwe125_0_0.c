#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Verificar si el puntero de precios es válido
    if (prices == NULL) {
        return -1;
    }
    
    // Verificar si el tamaño es válido
    if (size <= 0) {
        return -1;
    }
    
    // Verificar si el string de índice es válido
    if (index_str == NULL) {
        return -1;
    }
    
    // Eliminar espacios en blanco al principio y al final
    char *start = index_str;
    char *end = start + strlen(index_str) - 1;
    
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    // Verificar si el string está vacío después de eliminar espacios
    if (start > end) {
        return -1;
    }
    
    // Crear una copia del string procesado
    int length = end - start + 1;
    char *processed_str = (char*)malloc(length + 1);
    if (processed_str == NULL) {
        return -1;
    }
    
    strncpy(processed_str, start, length);
    processed_str[length] = '\0';
    
    // Convertir el string a entero
    char *endptr;
    long index = strtol(processed_str, &endptr, 10);
    
    // Liberar la memoria asignada
    free(processed_str);
    
    // Verificar si la conversión fue exitosa
    if (*endptr != '\0') {
        return -1;
    }
    
    // Verificar si el índice está dentro de los límites
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Devolver el precio en el índice especificado
    return prices[index];
}