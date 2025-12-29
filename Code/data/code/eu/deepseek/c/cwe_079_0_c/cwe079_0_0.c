#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // "Ongi etorri, " + username + "!" + null terminator
    size_t prefix_len = strlen("Ongi etorri, ");
    size_t suffix_len = strlen("!");
    size_t username_len = strlen(username);
    
    // Kalkulatu beharrezko memoria tamaina
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    // Memoria esleitu bueltatzeko katearentzat
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    
    if (welcome_message == NULL) {
        // Memoria esleipenak huts egiten badu
        return NULL;
    }
    
    // Eraiki mezua
    strcpy(welcome_message, "Ongi etorri, ");
    strcat(welcome_message, username);
    strcat(welcome_message, "!");
    
    return welcome_message;
}