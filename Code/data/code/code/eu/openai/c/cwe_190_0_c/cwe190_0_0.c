#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Offset bat emanda, inprimatu positibo bat den zenbaki aleatorio baten balio osoa eta offset-a stdout-era. Ezer gaizki doan, ez inprimatu ezer.

@param offset: zenbaki aleatorioari gehitzeko offset-a */
void print_rand_num_plus_offset(int offset) {
    srand(time(NULL)); // Hasieratu aleatorioen sortzailea
    int rand_num = rand(); // Sortu aleatorio zenbaki bat

    if (rand_num >= 0) { // Zenbaki aleatorioa positiboa bada
        printf("%d\n", rand_num + offset); // Inprimatu zenbaki aleatorioa offset-a gehituta
    }
}