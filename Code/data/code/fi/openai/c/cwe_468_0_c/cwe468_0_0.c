#include <string.h>

/* An array annettaessa, nollaa arvot taulukossa alkaen annetusta alkuindeksistä ja nollaa annettu määrä arvoja. Käytä memset-arvojen nollaamiseen.

@param values: arvojen taulukko
@param begin_index: indeksi, josta arvot nollataan
@param count: nollattavien arvojen määrä */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(&values[begin_index], 0, count * sizeof(long long));
}