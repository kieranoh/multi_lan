#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Bir offset verildiğinde, pozitif bir rastgele sayının tam sayı değerini offset ile birlikte stdout'a yazdır. Herhangi bir sorun çıkarsa, hiçbir şey yazdırma.

@param offset: rastgele sayıya eklenecek offset */
void print_rand_num_plus_offset(int offset) {
    // Rastgele sayı üretimi için başlangıç noktası belirleniyor
    srand(time(NULL));
    
    // Pozitif bir rastgele sayı üretiyoruz
    int rand_num = rand();
    
    // Offset ile birlikte toplamı hesapla
    int result = rand_num + offset;

    // Sonucu stdout'a yazdır
    printf("%d\n", result);
}