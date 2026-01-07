#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 构建用于比较的完整域名
    std::string full_domain = "https://" + domain;

    // 检查目标 URL 是否以提供的域名开头
    if (target.find(full_domain) == 0) {
        // 如果是，返回目标 URL
        return target;
    } else {
        // 否则，返回重定向到域的 URL
        return full_domain;
    }
}