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
    const url = new URL(target);
    const targetDomain = url.hostname;

    if (targetDomain.endsWith(domain)) {
        return target; // Return the target URL if it matches the domain
    } else {
        return `https://${domain}`; // Fallback to the domain URL
    }
}