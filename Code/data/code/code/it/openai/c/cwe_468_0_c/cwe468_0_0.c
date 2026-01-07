#include <string.h>

/* Data un array, ripristina i valori a 0 nell'array, partendo dall'indice di inizio fornito e ripristinando il numero di valori specificato. Usa memset per ripristinare i valori.

@param values: l'array di valori
@param begin_index: l'indice da cui iniziare a ripristinare i valori
@param count: il numero di valori da ripristinare */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // Gestione di errori: array nullo o indici non validi
    }

    // Usare memset per impostare a 0 i valori specificati
    memset(&values[begin_index], 0, count * sizeof(long long));
}