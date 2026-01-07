#include <string.h>

/* utilitzeu strncpy per copiar el contingut de src a dest tant com sigui possible

@param dest: el buffer de destinació
@param dest_size: la mida del buffer de destinació
@param src: el buffer font
@param src_size: la mida del buffer font */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Verificar punteros nulos
    if (dest == NULL || src == NULL) {
        return;
    }
    
    // Verificar tamaños válidos
    if (dest_size <= 0 || src_size <= 0) {
        return;
    }
    
    // Determinar cuántos caracteres podemos copiar
    // strncpy copia exactamente n caracteres, así que necesitamos asegurar
    // que no excedamos el tamaño del destino
    int copy_size;
    
    // Si src_size es menor que dest_size, podemos copiar todo src
    // pero debemos dejar espacio para el carácter nulo terminador
    if (src_size < dest_size) {
        copy_size = src_size;
    } else {
        // Si src_size es mayor o igual, copiamos hasta dest_size-1
        // para dejar espacio para el carácter nulo
        copy_size = dest_size - 1;
    }
    
    // Usar strncpy para copiar exactamente copy_size caracteres
    strncpy(dest, src, copy_size);
    
    // Asegurar terminación nula (strncpy no añade automáticamente el nulo
    // si copy_size >= dest_size, pero en nuestro caso siempre copiamos
    // menos que dest_size cuando src_size >= dest_size)
    if (copy_size < dest_size) {
        dest[copy_size] = '\0';
    } else {
        // Esto no debería ocurrir con nuestra lógica, pero por seguridad
        dest[dest_size - 1] = '\0';
    }
}