#include <string.h>

/* Dla tablicy, zresetuj wartości do 0 w tablicy, zaczynając od podanego indeksu początkowego i resetując podaną liczbę wartości. Użyj memset do zresetowania wartości.

@param values: tablica wartości
@param begin_index: indeks, od którego zaczyna się resetowanie wartości
@param count: liczba wartości do zresetowania */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(&values[begin_index], 0, count * sizeof(long long));
}