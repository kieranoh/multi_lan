#include <string.h>

/* Gegeben ist ein Array, setze die Werte im Array auf 0, beginnend vom angegebenen Startindex und setze die angegebene Anzahl von Werten zurück. Verwende memset, um die Werte zurückzusetzen.

@param values: das Array der Werte
@param begin_index: der Index, von dem aus die Werte zurückgesetzt werden
@param count: die Anzahl der zurückzusetzen Werte */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values != NULL && begin_index >= 0 && count > 0) {
        memset(&values[begin_index], 0, count * sizeof(long long));
    }
}