#include <stdio.h>
#include <string.h>

/* एक उपयोगकर्ता-इनपुट स्ट्रिंग दी गई है, स्ट्रिंग से अंतिम स्थानों को हटा दें। स्ट्रिंग को स्थान पर संशोधित किया जाना चाहिए। */
void trim_spaces(char* str) {
    int n = strlen(str);
    int end = n - 1;

    // अंतिम स्थानों को ढूंढें
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // स्ट्रिंग को नई लंबाई सेट करें
    str[end + 1] = '\0';
}