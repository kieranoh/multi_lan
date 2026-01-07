#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Offset bat emanda, inprimatu positibo bat den zenbaki aleatorio baten balio osoa eta offset-a stdout-era. Ezer gaizki doan, ez inprimatu ezer.
    
    @param offset: zenbaki aleatorioari gehitzeko offset-a */
    
    /* Hasieratu ausazko zenbaki sortzailea denbora-oinarriarekin */
    srand(time(NULL));
    
    /* Lortu ausazko zenbaki positiboa (0 eta RAND_MAX artean) */
    int random_num = rand();
    
    /* Egiaztatu ausazko zenbakia positiboa dela (rand()-ek beti itzultzen du 0 eta RAND_MAX arteko zenbakia, RAND_MAX positiboa da) */
    if (random_num < 0) {
        /* Ausazko zenbakia negatiboa bada, ez inprimatu ezer */
        return;
    }
    
    /* Kalkulatu emaitza ausazko zenbakia eta offset-a gehituta */
    long result = (long)random_num + (long)offset;
    
    /* Egiaztatu emaitza positiboa dela */
    if (result <= 0) {
        /* Emaitza ez bada positiboa, ez inprimatu ezer */
        return;
    }
    
    /* Inprimatu emaitza stdout-era */
    printf("%ld\n", result);
}