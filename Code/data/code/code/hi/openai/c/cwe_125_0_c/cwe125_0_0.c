#include <stdio.h>
#include <stdlib.h>

/* 
आइटम की कीमतों के एक ऐरे और एक उपयोगकर्ता द्वारा दिए गए स्ट्रिंग को ध्यान में रखते हुए, ऐरे में दिए गए इंडेक्स पर आइटम की कीमत लौटाएं।

@param prices: आइटम की कीमतों का ऐरे
@param size: ऐरे का आकार
@param index_str: इंडेक्स को इंगित करने वाला स्ट्रिंग
@return ऐरे में दिए गए इंडेक्स पर आइटम की कीमत 
*/
int get_price_at_index(int* prices, int size, char* index_str) {
    // स्ट्रिंग को पूर्णांक में परिवर्तित करना
    int index = atoi(index_str);
    
    // यदि इंडेक्स मान्य है तो कीमत लौटाएं
    if (index >= 0 && index < size) {
        return prices[index];
    }
    
    // अन्यथा, -1 लौटाएं जो कि एक त्रुटि संकेत है
    return -1;
}