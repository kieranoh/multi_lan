#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 正規表現を使用してターゲットURLが指定されたドメインに属しているか確認
    std::regex domain_regex(R"(https://([a-zA-Z0-9-]+\.)*(" + domain + r"(\:\d+)?(/.*)?)$)");

    // ドメインに基づくリダイレクトのURLを生成
    std::string fallback_url = "https://" + domain;

    // ターゲットURLが指定されたドメインの一部である場合はターゲットURLを返す
    if (std::regex_match(target, domain_regex)) {
        return target;
    } else {
        return fallback_url;
    }
}