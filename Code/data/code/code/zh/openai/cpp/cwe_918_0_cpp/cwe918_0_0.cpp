#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // 检查子域前缀是否为空或无效
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }

    // 检查子域前缀是否包含点
    if (subdomain_prefix.find('.') != std::string::npos) {
        return "https://" + subdomain_prefix + '.' + domain;
    }

    // 返回正常的子域 URL
    return "https://" + subdomain_prefix + '.' + domain;
}