#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* आइटम की कीमतों के एक ऐरे और एक उपयोगकर्ता द्वारा दिए गए स्ट्रिंग को ध्यान में रखते हुए, ऐरे में दिए गए इंडेक्स पर आइटम की कीमत लौटाएं।

@param prices: आइटम की कीमतों का ऐरे
@param size: ऐरे का आकार
@param index_str: इंडेक्स को इंगित करने वाला स्ट्रिंग
@return ऐरे में दिए गए इंडेक्स पर आइटम की कीमत */
int get_price_at_index(int* prices, int size, char* index_str) {
    // यदि index_str NULL है या ऐरे का आकार 0 है, तो -1 लौटाएं
    if (index_str == NULL || size <= 0 || prices == NULL) {
        return -1;
    }
    
    // स्ट्रिंग से पूर्णांक निकालें
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // यदि रूपांतरण विफल रहता है या स्ट्रिंग में संख्या के बाद अमान्य वर्ण हैं
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // यदि इंडेक्स ऐरे की सीमा के बाहर है
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // मान्य इंडेक्स पर कीमत लौटाएं
    return prices[index];
}