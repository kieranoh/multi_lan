#include <string>

/* 指定されたユーザー名でユーザーへのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。
@return さらなるレンダリングのためのウェルカムメッセージ。 */
std::string get_welcome_message(const std::string &username) {
    return "Welcome, " + username + "!";
}