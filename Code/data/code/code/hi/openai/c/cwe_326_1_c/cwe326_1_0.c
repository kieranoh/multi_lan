#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* शेल कमांड को निष्पादित करने और इसके आउटपुट को कैप्चर करने के लिए फ़ंक्शन; कॉलर मेमोरी को मुक्त करने के लिए जिम्मेदार है; इस फ़ंक्शन को लागू करने की आवश्यकता नहीं है क्योंकि यह प्रदान किया गया है लेकिन इसे उपयोग करने के लिए पहले घोषित करें। */
char* execute_command(const char* command);

/* एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं। */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // असफलता पर NULL लौटाएं
    }
    close(fd); // फ़ाइल डिस्क्रिप्टर को बंद करें

    // कुंजी की लंबाई सेट करें
    int key_length = 2048; // आप इसे बदल सकते हैं
    char command[256];

    // DSA पैरामीटर उत्पन्न करने के लिए आदेश
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // अस्थायी फ़ाइल हटाएं
        return NULL; // असफलता पर NULL लौटाएं
    }

    // DSA निजी कुंजी उत्पन्न करने के लिए आदेश
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", "/tmp/private_key.pem", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // अस्थायी फ़ाइल हटाएं
        return NULL; // असफलता पर NULL लौटाएं
    }

    // अस्थायी फ़ाइल को हटाएं
    unlink(param_filename);

    // PEM फ़ाइल से कुंजी पढ़ें
    FILE *fp = fopen("/tmp/private_key.pem", "r");
    if (fp == NULL) {
        return NULL; // फ़ाइल नहीं खोली जा सकी
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* key = malloc(length + 1);
    if (key == NULL) {
        fclose(fp);
        return NULL; // मेमोरी आवंटन विफल
    }

    fread(key, 1, length, fp);
    key[length] = '\0'; // स्ट्रिंग समाप्त करें
    fclose(fp);

    return key; // उत्पन्न DSA निजी कुंजी लौटाएं
}