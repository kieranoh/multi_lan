#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    int key_length = 2048; // 키 लांबी सेट करा
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // पाईपसह कमांड चालवा
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;

    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // कमांड चालवताना त्रुटी
    }

    // कमांडचा आउटपुट वाचा
    getline(&buffer, &size, fp);
    pclose(fp);

    // आउटपुट तपासा
    if (buffer == NULL) {
        return NULL; // आउटपुट वाचताना त्रुटी
    }

    // PEM स्वरूपात की परत करा
    return buffer;
}