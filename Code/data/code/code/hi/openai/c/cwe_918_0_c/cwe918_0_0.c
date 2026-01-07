#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // मेमोरी आवंटित करें जो अधिकतम URL लंबाई के लिए है
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL; // मेमोरी आवंटन विफल
    }

    // यदि उपडोमेन अमान्य है या खाली है तो केवल डोमेन लौटाएं
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // उपडोमेन के लिए URL बनाएँ
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url; // निर्मित URL लौटाएं
}