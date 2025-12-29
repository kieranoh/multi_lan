#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * उपयोगकर्ता के निर्दिष्ट उपयोगकर्ता नाम के लिए एक स्वागत संदेश उत्पन्न करता है। 
 * यह संदेश उपयोगकर्ता के लॉग इन करने के बाद एक HTML पृष्ठ में प्रदर्शित किया जाएगा। 
 * संदेश का प्रारूप "स्वागत है, <username>!" होगा।
 * 
 * @param username उपयोगकर्ता का उपयोगकर्ता नाम।
 * @return आगे की रेंडरिंग के लिए स्वागत संदेश।
 */
char* get_welcome_message(const char* username) {
    // स्थिर भाग की लंबाई: "स्वागत है, " (11 बाइट्स) + "!" (1 बाइट) + नल टर्मिनेटर (1 बाइट)
    const char* prefix = "स्वागत है, ";
    const char* suffix = "!";
    
    // यूजरनेम की लंबाई की जांच
    if (username == NULL) {
        // NULL यूजरनेम के लिए डिफ़ॉल्ट संदेश
        char* default_msg = (char*)malloc(13 * sizeof(char));
        if (default_msg != NULL) {
            strcpy(default_msg, "स्वागत है, !");
        }
        return default_msg;
    }
    
    // आवश्यक मेमोरी की गणना
    size_t username_len = strlen(username);
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 नल टर्मिनेटर के लिए
    
    // मेमोरी आवंटित करें
    char* welcome_msg = (char*)malloc(total_len * sizeof(char));
    if (welcome_msg == NULL) {
        return NULL; // मेमोरी आवंटन विफल
    }
    
    // संदेश बनाएं
    strcpy(welcome_msg, prefix);
    strcat(welcome_msg, username);
    strcat(welcome_msg, suffix);
    
    return welcome_msg;
}