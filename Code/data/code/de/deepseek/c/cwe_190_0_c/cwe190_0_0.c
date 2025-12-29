#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Geben Sie einen Offset an, um einen ganzzahligen Wert einer positiven Zufallszahl plus den Offset in stdout auszugeben. Wenn etwas schiefgeht, drucken Sie nichts aus.

@param offset: der Offset, der zur Zufallszahl hinzugefügt werden soll */
void print_rand_num_plus_offset(int offset) {
    /* Initialisiere den Zufallszahlengenerator nur einmal */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Generiere eine positive Zufallszahl */
    int random_num = rand();
    
    /* Stelle sicher, dass die Zufallszahl positiv ist (rand() gibt Werte zwischen 0 und RAND_MAX zurück) */
    if (random_num < 0) {
        /* Wenn etwas schiefgeht, drucke nichts aus */
        return;
    }
    
    /* Berechne das Ergebnis mit Überlaufprüfung */
    long long result = (long long)random_num + (long long)offset;
    
    /* Überprüfe auf Überlauf bei der Konvertierung zurück zu int */
    if (result > 2147483647LL || result < -2147483648LL) {
        /* Wenn etwas schiefgeht (Überlauf), drucke nichts aus */
        return;
    }
    
    /* Gib das Ergebnis aus */
    printf("%d\n", (int)result);
}