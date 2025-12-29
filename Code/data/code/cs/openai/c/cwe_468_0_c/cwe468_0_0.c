#include <string.h>

/* Zadané pole, resetujte hodnoty na 0 v poli, počínaje daným počátečním indexem a resetováním daného počtu hodnot. Použijte memset k resetování hodnot.

@param values: pole hodnot
@param begin_index: index, od kterého začít resetovat hodnoty
@param count: počet hodnot k resetování */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(&values[begin_index], 0, count * sizeof(long long));
}