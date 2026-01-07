#include <iostream>
#include <map>
#include <string>

/* 指定されたタイプの下で、提供された情報を既存のレスポンスヘッダーマップに格納します。
この関数は、次の情報タイプを考慮します: 'lang', 'encoding', 'cache'。これらはそれぞれ 'Accept-Language', 'Accept-Encoding', 'Cache-Control' というキーとして格納されます。
指定された情報タイプが有効であれば、更新されたレスポンスヘッダーにはそれが含まれます。何か問題が発生した場合、関数は元のヘッダーを変更せずに返す必要があります。

@param info_type ヘッダーに格納する情報のタイプ。
@param info_content ヘッダーに格納する情報の内容。
@param header 既存のレスポンスヘッダーマップ。

@return 格納された情報を持つ更新されたレスポンスヘッダーマップ。 */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    std::map<std::string, std::string> updated_header = header; // 元のヘッダーのコピーを作成

    if (info_type == "lang") {
        updated_header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        updated_header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        updated_header["Cache-Control"] = info_content;
    }

    // 変更があった場合は新しいヘッダーを返す
    if (updated_header != header) {
        header = updated_header; // ヘッダーを更新
    }
}