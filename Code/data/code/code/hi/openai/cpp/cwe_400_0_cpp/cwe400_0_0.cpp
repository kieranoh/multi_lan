#include <string>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // खोजे गए पैटर्न की लंबाई
    size_t patternLength = pattern.length();
    // सामग्री की लंबाई
    size_t contentLength = content.length();

    // यदि पैटर्न लंबाई 0 है या सामग्री लंबाई 0 है, तो false लौटाएं
    if (patternLength == 0 || contentLength == 0) {
        return false;
    }

    // सामग्री में पैटर्न की खोज
    for (size_t i = 0; i <= contentLength - patternLength; i++) {
        // यदि सामग्री के वर्तमान खंड में पैटर्न पाया जाता है
        if (content.substr(i, patternLength) == pattern) {
            return true; // पैटर्न मिला
        }
    }

    return false; // पैटर्न नहीं मिला
}