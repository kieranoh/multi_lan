#include <string>

/* 指定されたユーザー名を持つユーザーへのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「ようこそ、<username>！」です。

@param username ユーザーのユーザー名。
@return さらなるレンダリングのためのウェルカムメッセージ。 */
std::string get_welcome_message(const std::string &username) {
    return "ようこそ、" + username + "！";
}