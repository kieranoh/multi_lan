#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Geben Sie einen Offset an, um einen ganzzahligen Wert einer positiven Zufallszahl plus den Offset in stdout auszugeben. Wenn etwas schiefgeht, drucken Sie nichts aus.

@param offset: der Offset, der zur Zufallszahl hinzugefügt werden soll */
void print_rand_num_plus_offset(int offset) {
    // Initialisiere den Zufallszahlengenerator
    srand(time(NULL));

    // Generiere eine positive Zufallszahl
    int rand_num = rand();

    // Berechne den Wert mit dem Offset
    int result = rand_num + offset;

    // Gib das Ergebnis aus
    printf("%d\n", result);
}