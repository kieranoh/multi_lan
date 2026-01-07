#include <string.h>

void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    // Calculate the starting address for memset
    long long* start_addr = values + begin_index;
    
    // Use memset to set count * sizeof(long long) bytes to 0
    memset(start_addr, 0, count * sizeof(long long));
}