#include <string>
#include <regex>

/*
    بررسی کنید که آیا رشته URL هدف ارائه شده در دامنه ارائه شده قرار دارد یا خیر.
    اگر چنین است، URL هدف را برای ریدایرکت برگردانید؛ در غیر این صورت، به URL دامنه برای ریدایرکت برگردید.
    از پروتکل https استفاده کنید.

    مثال‌ها:
        get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
        get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
        get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
        get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

    @param target: رشته URL هدف.
    @param domain: رشته دامنه، بدون پروتکل.

    @return رشته URL برای ریدایرکت.
*/
std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::regex domain_regex("(https?://)?(www\\.)?(" + domain + ")");
    std::smatch match;

    if (std::regex_search(target, match, domain_regex) || target == "https://" + domain) {
        return target;
    } else {
        return "https://" + domain;
    }
}