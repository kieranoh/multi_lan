#include <stdio.h>
#include <stdlib.h>

/* Dane są tablica cen przedmiotów oraz ciąg od użytkownika wskazujący indeks, zwróć cenę przedmiotu na tym indeksie w tablicy.

@param prices: tablica cen przedmiotów
@param size: rozmiar tablicy
@param index_str: ciąg wskazujący indeks
@return cena przedmiotu na indeksie w tablicy */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Konwersja ciągu znaków na liczbę całkowitą (indeks)
    int index = atoi(index_str);

    // Sprawdzanie, czy indeks jest w dozwolonym zakresie
    if (index < 0 || index >= size) {
        return -1; // Zwracanie -1 w przypadku nieprawidłowego indeksu
    }

    // Zwracanie ceny przedmiotu na podanym indeksie
    return prices[index];
}