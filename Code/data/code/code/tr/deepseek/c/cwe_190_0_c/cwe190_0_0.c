#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Bir offset verildiğinde, pozitif bir rastgele sayının tam sayı değerini offset ile birlikte stdout'a yazdır. Herhangi bir sorun çıkarsa, hiçbir şey yazdırma.

@param offset: rastgele sayıya eklenecek offset */
void print_rand_num_plus_offset(int offset) {
    /* Rastgele sayı üretecini sadece bir kez başlat */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Rastgele sayı üret (pozitif olması için) */
    int random_num = rand();
    
    /* Rastgele sayının pozitif olduğundan emin ol */
    if (random_num < 0) {
        /* Eğer negatifse, hiçbir şey yazdırma */
        return;
    }
    
    /* Toplamı hesapla - taşma kontrolü yap */
    long long total = (long long)random_num + (long long)offset;
    
    /* Toplamın pozitif olduğundan emin ol */
    if (total <= 0) {
        /* Toplam pozitif değilse, hiçbir şey yazdırma */
        return;
    }
    
    /* Sonucu yazdır */
    printf("%lld\n", total);
}