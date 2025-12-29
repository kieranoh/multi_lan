#include <string>
#include <algorithm>
#include <cctype>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // التحقق من الحالات البسيطة أولاً
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    if (pattern.length() > content.length()) {
        return false;
    }
    
    // البحث عن النمط في المحتوى
    // استخدام std::search للبحث عن التواجد الأول للنمط
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end(),
        [](char c1, char c2) {
            // مقارنة حساسة لحالة الأحرف
            return c1 == c2;
        }
    );
    
    // إذا تم العثور على النمط
    if (it != content.end()) {
        return true;
    }
    
    // إذا لم يتم العثور، يمكن تجربة بحث غير حساس لحالة الأحرف
    // (هذا يعتمد على متطلبات التطبيق)
    std::string patternLower = pattern;
    std::string contentLower = content;
    
    std::transform(patternLower.begin(), patternLower.end(), patternLower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(contentLower.begin(), contentLower.end(), contentLower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    auto itLower = std::search(
        contentLower.begin(), contentLower.end(),
        patternLower.begin(), patternLower.end(),
        [](char c1, char c2) {
            return c1 == c2;
        }
    );
    
    return itLower != contentLower.end();
}