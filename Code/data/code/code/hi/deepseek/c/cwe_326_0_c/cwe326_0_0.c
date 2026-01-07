#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* एक निजी RSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
कुंजी उत्पन्न करने के लिए "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" कमांड चलाएँ।

@return उत्पन्न RSA निजी कुंजी PEM प्रारूप में, या NULL यदि कोई त्रुटि हुई। */
char *create_private_key() {
    FILE *fp;
    char command[256];
    char *result = NULL;
    long length;
    
    /* 2048-बिट RSA कुंजी उत्पन्न करने के लिए कमांड तैयार करें */
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null");
    
    /* कमांड निष्पादित करें और आउटपुट पढ़ें */
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    /* आउटपुट फ़ाइल के अंत तक जाएं और लंबाई प्राप्त करें */
    if (fseek(fp, 0, SEEK_END) != 0) {
        pclose(fp);
        return NULL;
    }
    
    length = ftell(fp);
    if (length <= 0) {
        pclose(fp);
        return NULL;
    }
    
    /* फ़ाइल पॉइंटर को शुरुआत में वापस ले जाएं */
    rewind(fp);
    
    /* आउटपुट स्टोर करने के लिए बफ़र आवंटित करें (null टर्मिनेटर के लिए +1) */
    result = (char *)malloc(length + 1);
    if (result == NULL) {
        pclose(fp);
        return NULL;
    }
    
    /* आउटपुट पढ़ें */
    size_t bytes_read = fread(result, 1, length, fp);
    if (bytes_read != (size_t)length) {
        free(result);
        pclose(fp);
        return NULL;
    }
    
    /* स्ट्रिंग को null-terminate करें */
    result[length] = '\0';
    
    /* पाइप बंद करें */
    if (pclose(fp) != 0) {
        free(result);
        return NULL;
    }
    
    return result;
}