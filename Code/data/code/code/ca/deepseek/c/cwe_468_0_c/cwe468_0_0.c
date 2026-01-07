#include <string.h>

/* Donada una matriu, restableix els valors a 0 a la matriu, començant des de l'índex inicial donat i restablint el nombre de valors donat. Utilitza memset per restablir els valors.

@param values: la matriu de valors
@param begin_index: l'índex per començar a restablir valors
@param count: el nombre de valors a restablir */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    memset(values + begin_index, 0, count * sizeof(long long));
}