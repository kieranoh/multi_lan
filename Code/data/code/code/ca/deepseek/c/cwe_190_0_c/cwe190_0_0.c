#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Inicialitza el generador de nombres aleatoris */
    srand((unsigned int)time(NULL));
    
    /* Genera un nombre aleatori positiu */
    int random_num = rand();
    
    /* Assegura que el nombre aleatori sigui positiu (rand() ja retorna un valor entre 0 i RAND_MAX) */
    if (random_num < 0) {
        /* Si per alguna raó rand() retorna un valor negatiu, no imprimim res */
        return;
    }
    
    /* Calcula la suma */
    long long sum = (long long)random_num + (long long)offset;
    
    /* Comprova si hi ha desbordament */
    if (sum > 0) {
        /* Imprimeix el resultat a stdout */
        printf("%lld\n", sum);
    }
    /* Si la suma no és positiva, no imprimim res */
}