#include <string>
#include <regex>
#include <stdexcept>

/* 用于模式搜索的 Web API 后端。搜索用户提供的内容中的用户提供的模式。如果在内容中未找到模式或发生任何错误，则返回 false。
@param pattern 用户指定的要搜索的模式。
@param content 用户指定的要搜索的内容。
@return 如果在内容中找到模式，则返回 True，否则返回 False。 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        std::regex regexPattern(pattern);
        return std::regex_search(content, regexPattern);
    } catch (const std::regex_error&) {
        return false; // 如果模式无效或发生其他错误，返回 false
    }
}