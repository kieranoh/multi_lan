#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Komut çıktısını almak için yeterli boyutta bir buffer ayırıyoruz.
    char *result = malloc(1024 * sizeof(char));
    if (result == NULL) {
        return ""; // Bellek tahsisi hatası
    }
    
    // Komutun çalıştırılması için bir dosya akışı açıyoruz.
    FILE *fp;
    char command[256];

    // `ls -l` komutunu hazırlıyoruz.
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);
    
    // Komutu çalıştırıyoruz ve stdout çıktısını okuyoruz.
    fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // Komut yürütme hatası
    }

    // Komut çıktısını okuyoruz.
    size_t index = 0;
    while (fgets(result + index, 1024 - index, fp) != NULL) {
        index += strlen(result + index);
        if (index >= 1024) {
            break; // Buffer dolu ise döngüyü kır
        }
    }

    // Komutun yürütülmesi tamamlandıktan sonra akışı kapatıyoruz.
    pclose(fp);
    
    return result; // Sonucu döndürüyoruz.
}