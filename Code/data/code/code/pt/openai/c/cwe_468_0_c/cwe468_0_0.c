#include <string.h>

/* Dada uma matriz, redefina os valores para 0 na matriz, começando do índice inicial fornecido e redefinindo o número de valores fornecido. Use memset para redefinir os valores.

@param values: a matriz de valores
@param begin_index: o índice para começar a redefinir os valores
@param count: o número de valores a serem redefinidos */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // Retorna se a matriz for nula ou índices inváldios
    }
    
    memset(&values[begin_index], 0, count * sizeof(long long));
}