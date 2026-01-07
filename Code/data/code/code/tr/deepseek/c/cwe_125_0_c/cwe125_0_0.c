#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* Bir dizi ürün fiyatı ve bir kullanıcıdan gelen indeks belirten bir dize verildiğinde, dizideki belirtilen indeksteki ürünün fiyatını döndür. */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Eğer dizi boşsa veya indeks dizesi NULL ise hata döndür
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // İndeks dizesini temizle: baştaki ve sondaki boşlukları kaldır
    char* start = index_str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
    
    // Boş dize kontrolü
    if (strlen(start) == 0) {
        return -1;
    }
    
    // Dizenin tamamının sayısal olup olmadığını kontrol et
    for (char* p = start; *p != '\0'; p++) {
        if (!isdigit((unsigned char)*p)) {
            return -1;
        }
    }
    
    // Sayıya dönüştür
    char* endptr;
    long int index = strtol(start, &endptr, 10);
    
    // Dönüşüm başarısız olduysa veya tüm dize tüketilmediyse
    if (*endptr != '\0') {
        return -1;
    }
    
    // Taşma kontrolü
    if (index < INT_MIN || index > INT_MAX) {
        return -1;
    }
    
    // İndeksin geçerliliğini kontrol et
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Fiyatı döndür
    return prices[index];
}