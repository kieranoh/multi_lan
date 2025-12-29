#include <string.h>

/* Gegeven een array, stel de waarden in de array in op 0, beginnend vanaf de gegeven beginindex en reset de gegeven aantal waarden. Gebruik memset om de waarden te resetten.

@param values: de array van waarden
@param begin_index: de index om te beginnen met het resetten van waarden
@param count: het aantal waarden om te resetten */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // Voorkom ongeldige invoer
    }
    memset(values + begin_index, 0, count * sizeof(long long));
}