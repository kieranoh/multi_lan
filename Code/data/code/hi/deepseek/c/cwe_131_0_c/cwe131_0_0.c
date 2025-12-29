#include <stdlib.h>
#include <string.h>

/* एक स्ट्रिंग दी गई है, स्ट्रिंग की एक डुप्लिकेट लौटाएं। डुप्लिकेट को हीप पर आवंटित किया जाना चाहिए, और कॉलर इसे मुक्त करने के लिए जिम्मेदार है।

@param str: डुप्लिकेट करने के लिए स्ट्रिंग
@return स्ट्रिंग की एक डुप्लिकेट */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* duplicate = (char*)malloc(len * sizeof(char));
    
    if (duplicate == NULL) {
        return NULL;
    }
    
    memcpy(duplicate, str, len);
    return duplicate;
}