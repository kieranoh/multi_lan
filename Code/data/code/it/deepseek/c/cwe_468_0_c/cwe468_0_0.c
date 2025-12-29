#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    // Controllo dei parametri per evitare comportamenti indefiniti
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // Calcola il puntatore all'elemento di partenza
    long long* start_ptr = values + begin_index;
    
    // Calcola il numero di byte da impostare a 0
    size_t bytes_to_zero = (size_t)count * sizeof(long long);
    
    // Usa memset per impostare i valori a 0
    memset(start_ptr, 0, bytes_to_zero);
}