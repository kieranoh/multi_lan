#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Elementu prezioen array bat eta erabiltzaile batek adierazitako indizea duen string bat emanda, arrayan indize horretan dagoen elementuaren prezioa itzuli. */
int get_price_at_index(int* prices, int size, char* index_str) {
    // String hutsa edo NULL pointerra bada, -1 itzuli
    if (index_str == NULL || strlen(index_str) == 0) {
        return -1;
    }
    
    // String guztia zenbaki balioduna den egiaztatu
    for (int i = 0; index_str[i] != '\0'; i++) {
        // Lehenengo karakterea minus zeinua bada, onartu
        if (i == 0 && index_str[i] == '-') {
            continue;
        }
        // Digitua ez bada, -1 itzuli
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // String-a zenbaki oso bihurtu
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Biheketa errorea egiaztatu
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // Indizea arrayaren tamainaren barruan dagoen egiaztatu
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Prezioa itzuli
    return prices[index];
}