#include <string>
#include <iostream>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // サブドメインが空または無効な場合、ドメインを返す
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-") != std::string::npos) {
        return "https://" + domain;
    }

    // サブドメインが有効な場合、URLを生成する
    return "https://" + subdomain_prefix + "." + domain;
}