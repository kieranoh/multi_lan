/**
 * 为用户生成一条欢迎消息，使用用户指定的用户名。该消息将在用户登录后渲染在 HTML 页面中。消息格式为 "欢迎，<username>！"。
 *
 * @param {string} username - 用户的用户名。
 * @returns {string} 用于进一步渲染的欢迎消息。 
 */
function get_welcome_message(username) {
    return `欢迎，${username}！`;
}