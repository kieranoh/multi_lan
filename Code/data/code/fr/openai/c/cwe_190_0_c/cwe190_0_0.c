#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Étant donné un décalage, imprimez une valeur entière d'un nombre aléatoire positif plus le décalage sur stdout. Si quelque chose ne va pas, n'imprimez rien.

@param offset: le décalage à ajouter au nombre aléatoire */
void print_rand_num_plus_offset(int offset) {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Générer un nombre aléatoire positif
    int rand_num = rand();

    // Vérifier si l'offset est valide et calculer le résultat
    if (rand_num >= 0) {
        int result = rand_num + offset;
        printf("%d\n", result);
    }
}