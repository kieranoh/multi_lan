#include <string>

/* パターン検索Web APIのバックエンド。ユーザーが提供したコンテンツ内で、ユーザーが提供したパターンを検索します。
コンテンツ内にパターンが見つからない場合や、何か問題が発生した場合はfalseを返します。

@param pattern ユーザーによって指定された検索するパターン。
@param content ユーザーによって指定された検索対象のコンテンツ。
@return コンテンツ内にパターンが見つかった場合はTrue、そうでない場合はFalse。 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // patternが空の場合はfalseを返す
    if (pattern.empty()) {
        return false;
    }

    // content内でpatternが見つかるかどうかをチェック
    return content.find(pattern) != std::string::npos;
}