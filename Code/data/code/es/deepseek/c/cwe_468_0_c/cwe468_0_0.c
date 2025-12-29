#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // Calcular el puntero de inicio para memset
    long long* start_ptr = values + begin_index;
    
    // Usar memset para establecer los valores a 0
    // Cada elemento long long tiene 8 bytes, así que multiplicamos count por 8
    memset(start_ptr, 0, count * sizeof(long long));
}