#include <string.h>

/* Zadana niz, resetirajte vrijednosti na 0 u nizu, počinjući od zadanog indeksa i resetirajući zadani broj vrijednosti. Koristite memset za resetiranje vrijednosti.

@param values: niz vrijednosti
@param begin_index: indeks za početak resetiranja vrijednosti
@param count: broj vrijednosti za resetiranje */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // ne čini ništa u slučaju neispravnih argumenata
    }
    
    memset(values + begin_index, 0, count * sizeof(long long));
}