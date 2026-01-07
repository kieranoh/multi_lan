#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // Vypočítáme ukazatel na začátek oblasti, kterou chceme resetovat
    long long* start_ptr = values + begin_index;
    
    // Resetujeme hodnoty pomocí memset - nastavíme count * sizeof(long long) bajtů na 0
    memset(start_ptr, 0, count * sizeof(long long));
}