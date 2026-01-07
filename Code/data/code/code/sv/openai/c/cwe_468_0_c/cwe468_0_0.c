#include <string.h>

/* Givet en array, återställ värdena till 0 i arrayen, med början från det angivna startindexet och återställ det angivna antalet värden. Använd memset för att återställa värdena.

@param values: arrayen av värden
@param begin_index: indexet för att börja återställa värden
@param count: antalet värden att återställa */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(&values[begin_index], 0, count * sizeof(long long));
}