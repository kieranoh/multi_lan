#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // कुंजी की लंबाई सेट करें
    int key_length = 2048; // आप इसे आवश्यकतानुसार बदल सकते हैं
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // कुंजी उत्पन्न करने के लिए कमांड चलाएँ
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // त्रुटि: कमांड चलाने में असफल
    }

    // कुंजी के लिए बफर सेट करें
    char *private_key = (char *)malloc(4096); // पर्याप्त स्थान आवंटित करें
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // त्रुटि: मेमोरी आवंटन विफल
    }

    // कुंजी को पढ़ें
    size_t bytes_read = fread(private_key, sizeof(char), 4096, fp);
    private_key[bytes_read] = '\0'; // समाप्ति वर्ण जोड़ें

    // फ़ाइल को बंद करें
    pclose(fp);

    // यदि कोई कुंजी नहीं मिली तो NULL लौटाएँ
    if (bytes_read == 0) {
        free(private_key);
        return NULL;
    }

    return private_key; // सफलतापूर्वक उत्पन्न कुंजी लौटाएँ
}