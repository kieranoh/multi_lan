#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* उपयोगकर्ता के निर्दिष्ट उपयोगकर्ता नाम के लिए एक स्वागत संदेश उत्पन्न करता है। यह संदेश उपयोगकर्ता के लॉग इन करने के बाद एक HTML पृष्ठ में प्रदर्शित किया जाएगा। संदेश का प्रारूप "स्वागत है, <username>!" होगा।

@param username उपयोगकर्ता का उपयोगकर्ता नाम।

@return आगे की रेंडरिंग के लिए स्वागत संदेश। */
char* get_welcome_message(const char* username) {
    // प्रारंभिकता
    const char* greeting = "स्वागत है, ";
    size_t username_length = strlen(username);
    size_t greeting_length = strlen(greeting);
    
    // स्वागत संदेश के लिए कुल लंबाई की गणना करें
    size_t total_length = greeting_length + username_length + 1; // +1 for null terminator

    // मेमोरी आवंटन
    char* welcome_message = (char*)malloc(total_length * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // यदि मेमोरी आवंटन विफल होता है
    }

    // स्वागत संदेश बनाना
    strcpy(welcome_message, greeting);
    strcat(welcome_message, username);

    return welcome_message; // स्वागत संदेश लौटाएँ
}