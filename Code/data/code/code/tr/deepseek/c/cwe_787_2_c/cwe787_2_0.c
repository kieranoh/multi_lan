#include <string.h>
#include <ctype.h>

/* Kullanıcı girişi olan bir dize verildiğinde, dizenin sonundaki boşlukları kaldırın. Dize yerinde değiştirilmelidir. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Son karakterden başlayarak boşlukları kontrol et
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Boşluk olmayan son karakterden sonraki yere null karakter koy
    str[i + 1] = '\0';
}