#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // Geçici dosya adı için bir dizi tahsis et
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // Dosya adı oluşturulamazsa NULL döndür
    }

    // Dosyayı yazma modunda aç
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // Dosya açılamazsa NULL döndür
    }

    // Sonuçları dosyaya yaz
    fprintf(file, "%s", results);
    
    // Dosyayı kapat
    fclose(file);

    // Dosya adını döndür
    return strdup(filename); // Dinamik olarak tahsis edilmiş bir kopyasını döndür
}