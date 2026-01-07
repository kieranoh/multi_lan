#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // مکمل راستہ تیار کریں
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);
    
    // فائل کو کھولیں
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        // اگر فائل نہیں ملی تو خالی سٹرنگ واپس کریں
        return strdup(""); // خالی سٹرنگ کی کاپی بنائیں
    }
    
    // فائل کی مواد کو پڑھیں
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // مواد کے لئے میموری مختص کریں
    char *content = (char *)malloc(length + 1);
    if (content == NULL) {
        fclose(file);
        return strdup(""); // خالی سٹرنگ کی کاپی بنائیں
    }
    
    // فائل کو پڑھیں
    fread(content, 1, length, file);
    content[length] = '\0'; // آخری میں نیل کیریکٹر شامل کریں
    
    // فائل بند کریں
    fclose(file);
    
    return content; // مواد واپس کریں
}