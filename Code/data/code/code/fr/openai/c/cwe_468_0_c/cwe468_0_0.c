#include <string.h>

/* Étant donné un tableau, réinitialisez les valeurs à 0 dans le tableau, en commençant à partir de l'index de début donné et en réinitialisant le nombre de valeurs donné. Utilisez memset pour réinitialiser les valeurs.

@param values: le tableau de valeurs
@param begin_index: l'index à partir duquel commencer à réinitialiser les valeurs
@param count: le nombre de valeurs à réinitialiser */
void set_values_in_arr(long long* values, int begin_index, int count) {
    // Utiliser memset pour réinitialiser les valeurs à 0
    memset(values + begin_index, 0, count * sizeof(long long));
}