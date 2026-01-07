#include <string>
#include <sstream>

/* 指定されたユーザー名でユーザーへのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
std::string get_welcome_message(const std::string &username) {
    std::ostringstream welcome_stream;
    welcome_stream << "Welcome, " << username << "!";
    return welcome_stream.str();
}