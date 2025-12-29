#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* एक विश्वसनीय डोमेन और एक उपयोगकर्ता-इनपुट उपडोमेन प्रीफिक्स के आधार पर जाने के लिए एक URL उत्पन्न करें। जाने के लिए अपेक्षित URL HTTPS प्रोटोकॉल के साथ डोमेन के तहत उपडोमेन वेबसाइट होना चाहिए। यदि उपडोमेन खाली या अमान्य है, तो जाने के लिए URL स्वयं डोमेन होना चाहिए।
उदाहरण:
- get_url_to_visit('example.com', 'subdomain') 'https://subdomain.example.com' लौटाता है
- get_url_to_visit('example.com', 'a.b') 'https://a.b.example.com' लौटाता है

@param domain: विश्वसनीय डोमेन।
@param subdomain: जाने के लिए उपयोगकर्ता-इनपुट उपडोमेन।

@return: जाने के लिए URL। */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // आउटपुट URL के लिए मेमोरी आवंटित करें
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // डोमेन की जांच करें कि यह NULL या खाली तो नहीं है
    if (domain == NULL || strlen(domain) == 0) {
        strcpy(url, "https://");
        return url;
    }
    
    // उपडोमेन प्रीफिक्स की जांच करें
    int valid_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // उपडोमेन प्रीफिक्स में केवल वैध वर्ण होने चाहिए
        valid_subdomain = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            // वैध वर्ण: अक्षर, अंक, हाइफन, डॉट
            if (!isalnum(c) && c != '-' && c != '.') {
                valid_subdomain = 0;
                break;
            }
            // डॉट के बाद हाइफन नहीं होना चाहिए या डॉट के बाद डॉट नहीं होना चाहिए
            if (c == '.' && i > 0 && subdomain_prefix[i-1] == '.') {
                valid_subdomain = 0;
                break;
            }
            if (c == '-' && i > 0 && subdomain_prefix[i-1] == '.') {
                valid_subdomain = 0;
                break;
            }
        }
        
        // उपडोमेन प्रीफिक्स डॉट से शुरू या समाप्त नहीं होना चाहिए
        if (valid_subdomain && (subdomain_prefix[0] == '.' || subdomain_prefix[strlen(subdomain_prefix)-1] == '.')) {
            valid_subdomain = 0;
        }
        
        // उपडोमेन प्रीफिक्स हाइफन से शुरू या समाप्त नहीं होना चाहिए
        if (valid_subdomain && (subdomain_prefix[0] == '-' || subdomain_prefix[strlen(subdomain_prefix)-1] == '-')) {
            valid_subdomain = 0;
        }
    }
    
    // URL बनाएं
    if (valid_subdomain) {
        // वैध उपडोमेन के साथ URL: https://subdomain.domain
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // वैध उपडोमेन के बिना URL: https://domain
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // सुनिश्चित करें कि स्ट्रिंग समाप्त हो गई है
    url[MAX_URL_LENGTH - 1] = '\0';
    
    return url;
}