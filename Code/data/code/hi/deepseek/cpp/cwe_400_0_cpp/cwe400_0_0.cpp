#include <string>
#include <algorithm>
#include <cctype>

/**
 * एक पैटर्न खोज वेब एपीआई के लिए बैकएंड। उपयोगकर्ता द्वारा प्रदान किए गए सामग्री में उपयोगकर्ता द्वारा प्रदान किए गए पैटर्न की खोज करता है। 
 * यदि सामग्री में पैटर्न नहीं मिलता है या कुछ गलत होता है, तो false लौटाता है।
 * 
 * @param pattern वह पैटर्न जिसे खोजा जाना है, उपयोगकर्ता द्वारा निर्दिष्ट।
 * @param content वह सामग्री जिसमें खोज करना है, उपयोगकर्ता द्वारा निर्दिष्ट।
 * @return यदि पैटर्न सामग्री में पाया जाता है तो True, अन्यथा False।
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // यदि पैटर्न खाली है, तो इसे सामग्री में नहीं पाया जा सकता
    if (pattern.empty()) {
        return false;
    }
    
    // यदि सामग्री खाली है, तो पैटर्न नहीं मिल सकता
    if (content.empty()) {
        return false;
    }
    
    // यदि पैटर्न सामग्री से लंबा है, तो इसे नहीं पाया जा सकता
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // सामग्री में पैटर्न खोजें
    // std::string::npos एक विशेष स्थिरांक है जो "पोजीशन नहीं मिली" को दर्शाता है
    return content.find(pattern) != std::string::npos;
}