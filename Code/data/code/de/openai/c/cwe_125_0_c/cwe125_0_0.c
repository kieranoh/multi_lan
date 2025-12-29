#include <stdio.h>
#include <stdlib.h>

/* Gegeben ist ein Array von Artikelpreisen und ein String von einem Benutzer, der den Index angibt, gib den Preis des Artikels am Index im Array zurück.

@param prices: das Array der Artikelpreise
@param size: die Größe des Arrays
@param index_str: der String, der den Index angibt
@return den Preis des Artikels am Index im Array */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Konvertiere den index_str in einen ganzzahligen Index
    int index = atoi(index_str);
    
    // Überprüfe, ob der Index innerhalb der Grenzen des Arrays liegt
    if (index < 0 || index >= size) {
        return -1; // Gibt -1 zurück, um anzuzeigen, dass der Index ungültig ist
    }
    
    // Gibt den Preis des Artikels am angegebenen Index zurück
    return prices[index];
}