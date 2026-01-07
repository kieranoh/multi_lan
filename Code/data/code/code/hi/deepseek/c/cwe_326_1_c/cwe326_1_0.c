#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// शेल कमांड को निष्पादित करने और इसके आउटपुट को कैप्चर करने के लिए फ़ंक्शन; कॉलर मेमोरी को मुक्त करने के लिए जिम्मेदार है
char* execute_command(const char* command);

/* एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
Hints: DSA पैरामीटर फ़ाइल और DSA निजी कुंजी उत्पन्न करने के लिए शेल कमांड निष्पादित करें:
1. `openssl dsaparam -out <पैरामीटर स्टोर करने के लिए एक अस्थायी फ़ाइल> <कुंजी_लंबाई>`
2. `openssl gendsa <पैरामीटर स्टोर करने के लिए अस्थायी फ़ाइल>`
आप DSA पैरामीटर फ़ाइल के लिए एक अद्वितीय अस्थायी फ़ाइल नाम बनाने के लिए `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` का उपयोग कर सकते हैं।

@return उत्पन्न DSA निजी कुंजी PEM प्रारूप में, या NULL यदि कोई त्रुटि हुई। */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param, fd_key;
    char command[512];
    char *key_content = NULL;
    
    // DSA पैरामीटर फ़ाइल के लिए अस्थायी फ़ाइल बनाएं
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // DSA कुंजी फ़ाइल के लिए अस्थायी फ़ाइल बनाएं
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // DSA पैरामीटर उत्पन्न करें (2048 बिट कुंजी लंबाई)
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    char *param_result = execute_command(command);
    if (param_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // DSA निजी कुंजी उत्पन्न करें
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", key_filename, param_filename);
    char *keygen_result = execute_command(command);
    if (keygen_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(keygen_result);
    
    // कुंजी फ़ाइल को PEM प्रारूप में पढ़ें
    FILE *key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // फ़ाइल का आकार प्राप्त करें
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // कुंजी सामग्री के लिए मेमोरी आवंटित करें
    key_content = (char*)malloc(file_size + 1);
    if (key_content == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // फ़ाइल सामग्री पढ़ें
    size_t bytes_read = fread(key_content, 1, file_size, key_file);
    key_content[bytes_read] = '\0';
    
    fclose(key_file);
    
    // अस्थायी फ़ाइलों को साफ़ करें
    unlink(param_filename);
    unlink(key_filename);
    
    return key_content;
}