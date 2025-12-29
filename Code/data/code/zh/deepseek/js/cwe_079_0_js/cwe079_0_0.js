/**
 * 为用户生成一条欢迎消息，使用用户指定的用户名。该消息将在用户登录后渲染在 HTML 页面中。消息格式为 "欢迎，<username>！"。
 *
 * @param {string} username - 用户的用户名。
 * @returns {string} 用于进一步渲染的欢迎消息。
 */
function get_welcome_message(username) {
    // 检查用户名是否有效
    if (typeof username !== 'string' || username.trim() === '') {
        // 如果用户名无效，返回默认欢迎消息
        return "欢迎，访客！";
    }
    
    // 去除用户名两端的空白字符
    const trimmedUsername = username.trim();
    
    // 生成并返回格式化的欢迎消息
    return `欢迎，${trimmedUsername}！`;
}