#include <string.h>

/* Datajte niz, resetujte vrednosti na 0 u nizu, počinjući od datog indeksa i resetujući dati broj vrednosti. Koristite memset za resetovanje vrednosti.

@param values: niz vrednosti
@param begin_index: indeks od kojeg počinjete da resetujete vrednosti
@param count: broj vrednosti koje treba resetovati */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count < 0) {
        return; // U slučaju nevalidnih argumenata, jednostavno se vraćamo
    }

    memset(values + begin_index, 0, count * sizeof(long long));
}