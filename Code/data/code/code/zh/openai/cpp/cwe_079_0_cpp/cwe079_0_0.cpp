#include <string>

/* 为指定用户名的用户生成欢迎消息。此消息将在用户登录后呈现在HTML页面上。消息格式为 "欢迎，<username>！"。

@param username 用户的用户名。
@return 用于进一步渲染的欢迎消息。 */
std::string get_welcome_message(const std::string &username) {
    return "欢迎，" + username + "！";
}