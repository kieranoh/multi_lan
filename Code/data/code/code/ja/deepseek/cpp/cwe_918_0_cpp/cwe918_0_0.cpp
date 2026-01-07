#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // サブドメインが空または無効な場合、ドメイン自体を返す
    if (subdomain_prefix.empty()) {
        return "https://" + domain;
    }
    
    // サブドメインの有効性をチェック（英数字、ドット、ハイフンのみ許可）
    bool is_valid = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
    });
    
    if (!is_valid) {
        return "https://" + domain;
    }
    
    // サブドメインがドットで始まったり終わったりしないようにチェック
    if (subdomain_prefix.front() == '.' || subdomain_prefix.back() == '.') {
        return "https://" + domain;
    }
    
    // 連続するドットをチェック
    if (subdomain_prefix.find("..") != std::string::npos) {
        return "https://" + domain;
    }
    
    // 有効なサブドメインの場合、完全なURLを構築
    return "https://" + subdomain_prefix + "." + domain;
}