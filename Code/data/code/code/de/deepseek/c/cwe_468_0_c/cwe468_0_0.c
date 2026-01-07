#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // Berechne den Startzeiger für memset
    long long* start_ptr = values + begin_index;
    
    // Setze die Werte auf 0
    memset(start_ptr, 0, count * sizeof(long long));
}