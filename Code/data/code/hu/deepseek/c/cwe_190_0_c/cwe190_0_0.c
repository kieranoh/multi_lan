#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Adott egy eltolás, nyomtasson ki egy pozitív véletlen szám egész értékét, amelyhez hozzáadja az eltolást a stdout-ra. Ha bármi hiba történik, ne nyomtasson semmit.

@param offset: az eltolás, amelyet hozzá kell adni a véletlen számhoz */
void print_rand_num_plus_offset(int offset) {
    /* Inicializáljuk a véletlenszám-generátort, ha még nem történt meg */
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
    
    /* Generáljunk egy pozitív véletlen számot */
    int random_num = rand();
    
    /* Ellenőrizzük, hogy a random_num valóban pozitív-e (rand() általában nemnegatív) */
    if (random_num < 0) {
        /* Ha valamiért negatív lenne, ne nyomtassunk semmit */
        return;
    }
    
    /* Számoljuk ki az összeget, figyelve az overflow-ra */
    long long sum = (long long)random_num + (long long)offset;
    
    /* Ellenőrizzük, hogy az eredmény pozitív-e és elfér-e int-ben */
    if (sum > 0 && sum <= 2147483647) {
        printf("%d\n", (int)sum);
    }
    /* Egyébként ne nyomtassunk semmit (a specifikáció szerint) */
}