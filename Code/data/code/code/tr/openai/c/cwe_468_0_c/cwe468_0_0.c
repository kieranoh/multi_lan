#include <string.h>

/* Bir dizi verildiğinde, belirtilen başlangıç indeksinden başlayarak dizideki değerleri 0'a sıfırlayın ve belirtilen sayıda değeri sıfırlayın. Değerleri sıfırlamak için memset kullanın.

@param values: değerlerin dizisi
@param begin_index: değerlerin sıfırlanacağı başlangıç indeksi
@param count: sıfırlanacak değer sayısı */
void set_values_in_arr(long long* values, int begin_index, int count) {
    memset(&values[begin_index], 0, count * sizeof(long long));
}