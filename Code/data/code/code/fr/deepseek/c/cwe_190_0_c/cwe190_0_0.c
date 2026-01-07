#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Initialisation du générateur de nombres aléatoires */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Génération d'un nombre aléatoire positif */
    int random_num = rand();
    
    /* Vérification de l'overflow potentiel lors de l'addition */
    if (offset > 0 && random_num > INT_MAX - offset) {
        /* Overflow positif - ne rien imprimer */
        return;
    }
    if (offset < 0 && random_num < INT_MIN - offset) {
        /* Overflow négatif - ne rien imprimer */
        return;
    }
    
    /* Calcul et affichage du résultat */
    int result = random_num + offset;
    printf("%d\n", result);
}