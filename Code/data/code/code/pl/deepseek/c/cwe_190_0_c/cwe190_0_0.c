#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Podaj przesunięcie, wydrukuj wartość całkowitą dodatniej liczby losowej powiększonej o przesunięcie na stdout. Jeśli coś pójdzie nie tak, nie drukuj nic.

@param offset: przesunięcie do dodania do liczby losowej */
void print_rand_num_plus_offset(int offset) {
    /* Inicjalizacja generatora liczb losowych */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Generowanie dodatniej liczby losowej */
    int random_num = rand();
    
    /* Upewnienie się, że liczba jest dodatnia (rand() zwraca liczbę z zakresu 0 do RAND_MAX) */
    if (random_num < 0) {
        return; /* Nie drukuj nic, jeśli coś poszło nie tak */
    }
    
    /* Dodanie przesunięcia */
    long long result = (long long)random_num + (long long)offset;
    
    /* Sprawdzenie przepełnienia */
    if (result > 0) {
        printf("%lld\n", result);
    }
    /* Jeśli wynik nie jest dodatni, nie drukuj nic */
}