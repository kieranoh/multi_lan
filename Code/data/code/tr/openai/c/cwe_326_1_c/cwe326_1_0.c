#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    // DSA anahtarı uzunluğunu belirtelim
    const int key_length = 2048; // 2048 bit DSA anahtarı
    char param_filename[] = "/tmp/tempXXXXXX"; // Geçici dosya adı
    int fd = mkstemp(param_filename); // Geçici dosya oluştur

    if (fd == -1) {
        return NULL; // Geçici dosya oluşturulamadıysa NULL döndür
    }
    close(fd); // Dosyayı kapatıyoruz

    // DSA parametrelerini oluşturmak için shell komutunu çalıştır
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Hata durumunda geçici dosyayı sil
        return NULL;
    }

    // DSA özel anahtarını oluşturmak için shell komutunu çalıştır
    snprintf(command, sizeof(command), "openssl gendsa -out /tmp/dsa_private_key.pem %s", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Hata durumunda geçici dosyayı sil
        return NULL;
    }

    // Geçici dosyayı sil
    unlink(param_filename);

    // Özel anahtarın içeriğini okuyalım
    FILE *key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        return NULL; // Dosya açılamadıysa NULL döndür
    }

    // Dosya içeriği için bellek ayırma
    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char *key_content = (char*)malloc(key_length + 1);
    if (key_content == NULL) {
        fclose(key_file);
        return NULL; // Bellek ayırma hatası
    }

    fread(key_content, 1, key_length, key_file);
    key_content[key_length] = '\0'; // Null terminator ekle

    fclose(key_file);
    return key_content; // DSA özel anahtarını döndür
}