#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * एक URL उत्पन्न करें जो दिए गए API URL और उपयोगकर्ता ID के आधार पर उपयोगकर्ता जानकारी को क्वेरी करने के लिए हो।
 * क्वेरी के लिए अपेक्षित URL API URL और उपयोगकर्ता ID को जोड़कर होना चाहिए।
 * यदि उपयोगकर्ता ID खाली या अमान्य है, तो फ़ंक्शन NULL लौटाना चाहिए ताकि कोई क्वेरी न की जाए।
 * 
 * @param api_url: उपयोगकर्ता जानकारी को क्वेरी करने के लिए API URL।
 * @param user_id: क्वेरी करने के लिए उपयोगकर्ता ID।
 * 
 * @return क्वेरी के लिए URL। यदि उपयोगकर्ता ID खाली या अमान्य है, तो NULL लौटाएं।
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // यदि user_id NULL है या खाली स्ट्रिंग है, तो NULL लौटाएं
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // user_id की वैधता की जाँच करें (केवल अल्फ़ान्यूमेरिक वर्णों की अनुमति है)
    for (int i = 0; user_id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // यदि api_url NULL है, तो NULL लौटाएं
    if (api_url == NULL) {
        return NULL;
    }
    
    // आवश्यक मेमोरी की गणना करें: api_url + '/' + user_id + null टर्मिनेटर
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // मेमोरी आवंटित करें
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // मेमोरी आवंटन विफल
    }
    
    // URL बनाएं
    snprintf(result, total_len, "%s/%s", api_url, user_id);
    
    return result;
}