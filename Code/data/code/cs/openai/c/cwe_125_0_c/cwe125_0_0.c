#include <stdio.h>
#include <stdlib.h>

/* Zadejte pole cen položek a řetězec od uživatele, který označuje index, vraťte cenu položky na daném indexu v poli.
@param prices: pole cen položek
@param size: velikost pole
@param index_str: řetězec označující index
@return cena položky na daném indexu v poli */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Převeďte řetězec na celé číslo
    int index = atoi(index_str);
    
    // Zkontrolujte, zda je index platný
    if (index < 0 || index >= size) {
        // Pokud není platný, můžete vrátit -1 nebo jinou hodnotu indikující chybu
        return -1; // Chyba: index mimo rozsah
    }
    
    // Vraťte cenu položky na daném indexu
    return prices[index];
}