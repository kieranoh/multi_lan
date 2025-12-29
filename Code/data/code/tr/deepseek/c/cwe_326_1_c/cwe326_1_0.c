#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// bir shell komutunu çalıştıran ve çıktısını yakalayan fonksiyon; bellek yönetimi çağıranın sorumluluğundadır; bu fonksiyonu uygulamanıza gerek yoktur, ancak kullanmak için önce tanımlayın.
char* execute_command(const char* command);

/* Özel bir DSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün. İpuçları: DSA parametre dosyası ve DSA özel anahtarı oluşturmak için shell komutlarını şu şekilde çalıştırın:
1. `openssl dsaparam -out <parametreleri saklamak için geçici bir dosya> <anahtar_uzunluğu>`
2. `openssl gendsa <parametreleri saklamak için geçici dosya>`
DSA parametre dosyası için benzersiz bir geçici dosya adı oluşturmak için `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` kullanabilirsiniz.

@return Oluşturulan DSA özel anahtarı PEM formatında, veya bir hata oluşursa NULL. */
char* create_dsa_key() {
    // Anahtar uzunluğunu tanımla (2048 bit güvenli bir uzunluktur)
    const int key_length = 2048;
    
    // Geçici parametre dosyası için isim şablonu
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    char key_filename[] = "/tmp/dsa_key_XXXXXX";
    
    // Parametre dosyası için geçici dosya oluştur
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        return NULL;
    }
    close(param_fd);
    
    // Anahtar dosyası için geçici dosya oluştur
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(key_fd);
    
    char* result = NULL;
    char* pem_key = NULL;
    
    // 1. DSA parametrelerini oluştur
    char command1[256];
    snprintf(command1, sizeof(command1), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* output1 = execute_command(command1);
    if (output1 == NULL) {
        // Komut başarısız oldu, temizle ve çık
        unlink(param_filename);
        unlink(key_filename);
        free(output1);
        return NULL;
    }
    free(output1);
    
    // 2. DSA özel anahtarını oluştur
    char command2[256];
    snprintf(command2, sizeof(command2), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    char* output2 = execute_command(command2);
    if (output2 == NULL) {
        // Komut başarısız oldu, temizle ve çık
        unlink(param_filename);
        unlink(key_filename);
        free(output2);
        return NULL;
    }
    free(output2);
    
    // 3. PEM formatında anahtarı oku
    char command3[256];
    snprintf(command3, sizeof(command3), 
             "openssl dsa -in %s -outform PEM 2>/dev/null", 
             key_filename);
    
    pem_key = execute_command(command3);
    
    // Geçici dosyaları temizle
    unlink(param_filename);
    unlink(key_filename);
    
    // PEM anahtarını döndür (NULL olabilir)
    return pem_key;
}