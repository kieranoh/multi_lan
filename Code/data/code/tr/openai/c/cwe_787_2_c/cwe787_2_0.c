#include <stdio.h>
#include <string.h>

/* Kullanıcı girişi olan bir dize verildiğinde, dizenin sonundaki boşlukları kaldırın. Dize yerinde değiştirilmelidir. */
void trim_spaces(char* str) {
    int len = strlen(str);
    int end = len - 1;

    // Boşlukların sonundan başlayarak geri git
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // Sonuç dizesinin sonunu ayarla
    str[end + 1] = '\0';
}