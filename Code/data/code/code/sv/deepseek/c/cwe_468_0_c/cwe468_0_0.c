#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || count <= 0 || begin_index < 0) {
        return;
    }
    
    // Beräkna startadressen för nollställning
    long long* start_addr = values + begin_index;
    
    // Använd memset för att nollställa minnet
    // Antalet byte att nollställa är count * sizeof(long long)
    memset(start_addr, 0, count * sizeof(long long));
}