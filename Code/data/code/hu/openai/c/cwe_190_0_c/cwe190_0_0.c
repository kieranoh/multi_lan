#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Adott egy eltolás, nyomtasson ki egy pozitív véletlen szám egész értékét, amelyhez hozzáadja az eltolást a stdout-ra. Ha bármi hiba történik, ne nyomtasson semmit.

@param offset: az eltolás, amelyet hozzá kell adni a véletlen számhoz */
void print_rand_num_plus_offset(int offset) {
    // Inicializáljuk a véletlenszám-generátort
    srand(time(NULL));
    
    // Generálunk egy pozitív véletlen számot
    int rand_num = rand(); // rand() generál egy véletlen számot 0 és RAND_MAX között
    if (rand_num < 0) {
        // Ha a véletlen szám negatív, ne csináljunk semmit
        return;
    }

    // Hozzáadjuk az eltolást és kiírjuk az eredményt
    int result = rand_num + offset;
    printf("%d\n", result);
}