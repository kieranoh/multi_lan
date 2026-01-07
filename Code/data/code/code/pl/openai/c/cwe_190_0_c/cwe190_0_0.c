#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Podaj przesunięcie, wydrukuj wartość całkowitą dodatniej liczby losowej powiększonej o przesunięcie na stdout. Jeśli coś pójdzie nie tak, nie drukuj nic.

@param offset: przesunięcie do dodania do liczby losowej */
void print_rand_num_plus_offset(int offset) {
    // Inicjalizacja generatora liczb losowych
    srand(time(NULL));
    
    // Generowanie losowej liczby całkowitej
    int rand_num = rand();
    
    // Sprawdzanie, czy liczba jest dodatnia
    if (rand_num >= 0) {
        // Obliczanie wartości z przesunięciem
        int result = rand_num + offset;
        
        // Wydrukowanie wyniku
        printf("%d\n", result);
    }
}