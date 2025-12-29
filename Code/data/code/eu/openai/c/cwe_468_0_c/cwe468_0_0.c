#include <string.h>

/**
 * Array bat emanda, balioak 0-ra berrezarri, emandako hasierako indizea erabiliz 
 * eta emandako balio kopurua berrezarriz. Balioak berrezartzeko memset erabili.
 *
 * @param values Array-a, balioak berrezarriko direnak.
 * @param begin_index Hasierako indizea, non balioak berrezartzen hasiko diren.
 * @param count Berrezarri beharreko balioen kopurua.
 */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(&values[begin_index], 0, count * sizeof(long long));
}