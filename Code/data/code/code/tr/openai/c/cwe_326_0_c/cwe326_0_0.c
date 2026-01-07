#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    int key_length = 2048; // RSA anahtar uzunluğu
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Komutu çalıştır ve bir dosyaya yaz
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Hata durumunda NULL döndür
    }

    // Çıktıyı okumak için bir tampon ayarlayın
    char *buffer = malloc(4096);
    if (buffer == NULL) {
        pclose(fp);
        return NULL; // Hata durumunda NULL döndür
    }

    // Çıktıyı okuyun
    size_t read_size = fread(buffer, 1, 4096 - 1, fp);
    buffer[read_size] = '\0'; // Null terminatör ekle

    // Komut işlemeyi kapat
    if (pclose(fp) == -1) {
        free(buffer);
        return NULL; // Hata durumunda NULL döndür
    }

    return buffer; // Oluşturulan RSA özel anahtarını döndür
}