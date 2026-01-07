#include <string>
#include <algorithm>
#include <regex>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // 检查输入是否有效
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    // 使用标准库的搜索算法进行模式匹配
    // 这里使用 std::search 进行简单的子串搜索
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end(),
        [](char c1, char c2) {
            // 不区分大小写的搜索
            return std::tolower(static_cast<unsigned char>(c1)) == 
                   std::tolower(static_cast<unsigned char>(c2));
        }
    );
    
    // 如果找到模式，返回 true
    return it != content.end();
}