#include <string>
#include <cctype>
#include <algorithm>
#include <stdexcept>

// ヘルパー関数：文字列を小文字に変換
std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// ヘルパー関数：URLからプロトコルを除去してホスト名を抽出
std::string extract_host_from_url(const std::string& url) {
    // URLが空の場合は例外をスロー
    if (url.empty()) {
        throw std::invalid_argument("URL cannot be empty");
    }
    
    // "https://" または "http://" で始まるか確認
    std::string lower_url = to_lower(url);
    size_t protocol_start = 0;
    
    if (lower_url.find("https://") == 0) {
        protocol_start = 8; // "https://" の長さ
    } else if (lower_url.find("http://") == 0) {
        protocol_start = 7; // "http://" の長さ
    } else {
        // プロトコルがない場合はそのまま返す
        return url;
    }
    
    // プロトコル部分を除去
    std::string without_protocol = url.substr(protocol_start);
    
    // 最初の '/' または '?' または '#' を見つけてパス部分を除去
    size_t path_start = without_protocol.find_first_of("/?#");
    if (path_start != std::string::npos) {
        return without_protocol.substr(0, path_start);
    }
    
    return without_protocol;
}

// ヘルパー関数：ドメインが一致するか確認（サブドメインも含む）
bool is_domain_match(const std::string& host, const std::string& domain) {
    if (host.empty() || domain.empty()) {
        return false;
    }
    
    std::string lower_host = to_lower(host);
    std::string lower_domain = to_lower(domain);
    
    // 完全一致の場合
    if (lower_host == lower_domain) {
        return true;
    }
    
    // サブドメインの場合：ホストが ".domain" で終わるか確認
    if (lower_host.length() > lower_domain.length() + 1) {
        if (lower_host[lower_host.length() - lower_domain.length() - 1] == '.' &&
            lower_host.substr(lower_host.length() - lower_domain.length()) == lower_domain) {
            return true;
        }
    }
    
    return false;
}

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 入力バリデーション
    if (domain.empty()) {
        throw std::invalid_argument("Domain cannot be empty");
    }
    
    if (target.empty()) {
        return "https://" + domain;
    }
    
    try {
        // ターゲットURLからホスト名を抽出
        std::string target_host = extract_host_from_url(target);
        
        // ドメインが一致するか確認
        if (is_domain_match(target_host, domain)) {
            // ターゲットがすでにhttpsで始まっているか確認
            std::string lower_target = to_lower(target);
            if (lower_target.find("https://") == 0 || lower_target.find("http://") == 0) {
                // 既にプロトコルがある場合はそのまま返す
                return target;
            } else {
                // プロトコルがない場合はhttpsを追加
                return "https://" + target;
            }
        } else {
            // ドメインが一致しない場合はドメインURLにフォールバック
            return "https://" + domain;
        }
    } catch (const std::exception& e) {
        // エラーが発生した場合はドメインURLにフォールバック
        return "https://" + domain;
    }
}