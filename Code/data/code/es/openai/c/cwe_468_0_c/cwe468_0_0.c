#include <string.h>

/* Dada una matriz, restablece los valores a 0 en la matriz, comenzando desde el índice de inicio dado y restableciendo el número de valores dado. Usa memset para restablecer los valores.

@param values: la matriz de valores
@param begin_index: el índice para comenzar a restablecer valores
@param count: el número de valores a restablecer */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // Validación de entrada
    }
    memset(values + begin_index, 0, count * sizeof(long long));
}