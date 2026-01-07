#include <string.h>

/* Дан массив, сбросьте значения в массиве на 0, начиная с указанного начального индекса и сбрасывая указанное количество значений. Используйте memset для сброса значений.

@param values: массив значений
@param begin_index: индекс, с которого начинать сброс значений
@param count: количество значений для сброса */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // Проверка на корректность входных данных
    }
    
    memset(&values[begin_index], 0, count * sizeof(long long));
}