#include <string.h>

/* Adott egy tömb, állítsd vissza az értékeket 0-ra a tömbben, a megadott kezdő indexből, és állítsd vissza a megadott számú értéket. Használj memset-et az értékek visszaállításához.

@param values: az értékek tömbje
@param begin_index: az index, ahonnan az értékek visszaállítása kezdődik
@param count: a visszaállítandó értékek száma */
void set_values_in_arr(long long* values, int begin_index, int count) {
    if (values == NULL || begin_index < 0 || count <= 0) {
        return;
    }
    
    memset(values + begin_index, 0, count * sizeof(long long));
}