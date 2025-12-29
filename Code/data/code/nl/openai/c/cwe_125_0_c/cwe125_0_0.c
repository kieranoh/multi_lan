#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Gegeven een array van itemprijzen en een string van een gebruiker die de index aangeeft, retourneer de prijs van het item op de index in de array.

@param prices: de array van itemprijzen
@param size: de grootte van de array
@param index_str: de string die de index aangeeft
@return de prijs van het item op de index in de array */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Converteer de index string naar een integer
    int index = atoi(index_str);
    
    // Controleer of de index binnen de geldige range valt
    if (index < 0 || index >= size) {
        return -1; // Geef -1 terug als de index ongeldig is
    }
    
    // Geef de prijs op de opgegeven index terug
    return prices[index];
}