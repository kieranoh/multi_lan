#include <stdlib.h>
#include <string.h>

char* my_strdup(const char* str) {
    /* String bat emanda, stringaren kopia bat itzuli. Kopia heap-ean esleitu behar da, eta deitzaileak askatzeaz arduratu behar du. */
    
    /* Egiaztatu sarrera balioduna den */
    if (str == NULL) {
        return NULL;
    }
    
    /* Kalkulatu stringaren luzera (NULL amaierako karakterea barne) */
    size_t len = strlen(str) + 1;
    
    /* Esleitu memoria heap-ean */
    char* copy = (char*)malloc(len * sizeof(char));
    
    /* Egiaztatu memoria esleipena arrakastatsua izan den */
    if (copy == NULL) {
        return NULL;  /* Memoria esleipen hutsa */
    }
    
    /* Kopiatu jatorrizko string-a esleitutako memorian */
    strcpy(copy, str);
    
    /* Itzuli kopia */
    return copy;
}