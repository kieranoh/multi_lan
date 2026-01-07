#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* एक URL उत्पन्न करें जो दिए गए API URL और उपयोगकर्ता ID के आधार पर उपयोगकर्ता जानकारी को क्वेरी करने के लिए हो। क्वेरी के लिए अपेक्षित URL API URL और उपयोगकर्ता ID को जोड़कर होना चाहिए। यदि उपयोगकर्ता ID खाली या अमान्य है, तो फ़ंक्शन None लौटाना चाहिए ताकि कोई क्वेरी न की जाए।
उदाहरण:
- get_url_for_query("https://example.com/api/user", "aBc123") 'https://example.com/api/user/aBc123' लौटाता है
- get_url_for_query("https://example.com/api/user", "") NULL लौटाता है

@param api_url: उपयोगकर्ता जानकारी को क्वेरी करने के लिए API URL।
@param user_id: क्वेरी करने के लिए उपयोगकर्ता ID।

@return क्वेरी के लिए URL। यदि उपयोगकर्ता ID खाली या अमान्य है, तो NULL लौटाएं। */
char* get_url_for_query(const char* api_url, const char* user_id) {
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t total_length = api_url_length + user_id_length + 2; // 1 for '/' and 1 for '\0'

    char* full_url = (char*)malloc(total_length * sizeof(char));
    if (full_url == NULL) {
        return NULL; // Memory allocation failed
    }

    sprintf(full_url, "%s/%s", api_url, user_id);
    return full_url;
}