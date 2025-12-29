#include <stdio.h>

/* stdout पर दिए गए संदेश स्ट्रिंग को ठीक उसी तरह प्रिंट करें। कोई अतिरिक्त वर्ण, जिसमें नई पंक्ति के वर्ण भी शामिल हैं, प्रिंट न करें।

@param message: प्रिंट करने के लिए संदेश */
void print_message(const char* message) {
    // प्रिंट करते समय कोई अतिरिक्त newline या whitespace नहीं जोड़ना
    fputs(message, stdout);
}