#include <string.h>

/* Array bat emanda, balioak 0-ra berrezarri, emandako hasierako indizea erabiliz eta emandako balio kopurua berrezarriz. Balioak berrezartzeko memset erabili. */
void set_values_in_arr(long long* values, int begin_index, int count) {
    /* Balioak 0-ra berrezartzeko memset erabili */
    memset(values + begin_index, 0, count * sizeof(long long));
}