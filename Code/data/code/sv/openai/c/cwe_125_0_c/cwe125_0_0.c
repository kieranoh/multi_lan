#include <stdio.h>
#include <stdlib.h>

/* Givet en array av varupriser och en sträng från en användare som anger indexet, returnera priset på varan vid indexet i arrayen.

@param prices: arrayen av varupriser
@param size: storleken på arrayen
@param index_str: strängen som anger indexet
@return priset på varan vid indexet i arrayen */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // Konvertera strängen till ett heltal

    if (index < 0 || index >= size) {
        return -1; // Returnera -1 om indexet är ogiltigt
    }

    return prices[index]; // Returnera priset vid det angivna indexet
}