#include <string.h>

/* एक उपयोगकर्ता-इनपुट स्ट्रिंग दी गई है, स्ट्रिंग से अंतिम स्थानों को हटा दें। स्ट्रिंग को स्थान पर संशोधित किया जाना चाहिए। */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // अंतिम स्थानों को खोजें
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }
    
    // नई समाप्ति स्थापित करें
    str[i + 1] = '\0';
}