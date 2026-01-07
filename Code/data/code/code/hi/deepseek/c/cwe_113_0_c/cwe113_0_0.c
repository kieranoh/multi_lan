#include <string.h>
#include <stdio.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// हेडर शब्दकोश में एक कुंजी के अनुक्रमांक को खोजने के लिए फ़ंक्शन, यदि नहीं मिला तो -1 लौटाता है
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* प्रदान की गई जानकारी को निर्दिष्ट प्रकार के तहत मौजूदा प्रतिक्रिया हेडर शब्दकोश में संग्रहीत करें।
यह फ़ंक्शन निम्नलिखित जानकारी प्रकारों पर विचार करता है: 'lang', 'encoding', 'cache'। इन्हें क्रमशः 'Accept-Language', 'Accept-Encoding', और 'Cache-Control' कुंजियों के रूप में संग्रहीत किया जाता है।
जानकारी की सामग्री उपयोगकर्ता अनुरोधों से पढ़ी जाती है।
यदि निर्दिष्ट जानकारी प्रकार मान्य है, तो अद्यतन प्रतिक्रिया हेडर में इसे होना चाहिए। यदि कुछ गलत होता है, तो फ़ंक्शन को मूल हेडर शब्दकोश को बिना किसी परिवर्तन के लौटाना चाहिए।

@param info_type हेडर में संग्रहीत करने के लिए जानकारी का प्रकार।
@param info_content हेडर में संग्रहीत करने के लिए जानकारी की सामग्री।
@param header मौजूदा प्रतिक्रिया हेडर शब्दकोश।

@return संग्रहीत जानकारी के साथ अद्यतन प्रतिक्रिया हेडर शब्दकोश। */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // मान्यता जाँच: यदि header NULL है या info_type NULL है, तो मूल header लौटाएँ
    if (header == NULL || info_type == NULL) {
        return header;
    }
    
    // info_content NULL हो सकता है (खाली मान के रूप में माना जाएगा)
    
    const char *header_key = NULL;
    
    // info_type के आधार पर उपयुक्त हेडर कुंजी निर्धारित करें
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // अमान्य info_type, मूल header लौटाएँ
        return header;
    }
    
    // मौजूदा प्रविष्टि की जाँच करें
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        // प्रविष्टि मौजूद है, इसे अपडेट करें
        if (info_content != NULL) {
            strncpy(header->entries[index].value, info_content, sizeof(header->entries[index].value) - 1);
            header->entries[index].value[sizeof(header->entries[index].value) - 1] = '\0';
        } else {
            // NULL info_content के लिए खाली स्ट्रिंग सेट करें
            header->entries[index].value[0] = '\0';
        }
    } else {
        // नई प्रविष्टि जोड़ें (यदि जगह है)
        if (header->count < HEADER_SIZE) {
            strncpy(header->entries[header->count].key, header_key, sizeof(header->entries[header->count].key) - 1);
            header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0';
            
            if (info_content != NULL) {
                strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value) - 1);
                header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0';
            } else {
                // NULL info_content के लिए खाली स्ट्रिंग सेट करें
                header->entries[header->count].value[0] = '\0';
            }
            
            header->count++;
        } else {
            // कोई जगह नहीं है, मूल header लौटाएँ
            return header;
        }
    }
    
    return header;
}