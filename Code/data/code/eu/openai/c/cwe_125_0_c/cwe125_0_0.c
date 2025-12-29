#include <stdio.h>
#include <stdlib.h>

/* Elementu prezioen array bat eta erabiltzaile batek adierazitako indizea duen string bat emanda, arrayan indize horretan dagoen elementuaren prezioa itzuli. */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // String-a osorik zenbakira bihurtu
    if (index < 0 || index >= size) { // Indizea mugarik kanpo badago
        return -1; // -1 itzuli balio baliogabea adierazteko
    }
    return prices[index]; // Prezioa itzuli indizean
}