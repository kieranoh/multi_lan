/**
 * 检查提供的目标 URL 字符串是否在提供的域内。
 * 如果是，则返回用于重定向的目标 URL；否则，回退到用于重定向的域 URL。
 * 使用 https 协议。
 *
 * 示例：
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - 目标 URL 字符串。
 * @param {string} domain - 域字符串，不带协议。
 * @returns {string} 用于重定向的 URL 字符串。
 */
function get_target_for_redirect(target, domain) {
    try {
        // 解析目标 URL
        const targetUrl = new URL(target);
        
        // 检查目标 URL 的主机名是否以域结尾（支持子域）
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // 确保使用 https 协议
            targetUrl.protocol = 'https:';
            return targetUrl.toString();
        }
    } catch (error) {
        // 如果目标 URL 无效，则忽略错误并回退到域 URL
    }
    
    // 回退到域 URL，使用 https 协议
    return `https://${domain}`;
}