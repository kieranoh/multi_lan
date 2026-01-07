/**
 * 根据受信任的域和用户输入的子域前缀生成要访问的 URL。预期访问的 URL 应该是带有 HTTPS 协议的域下的子域网站。如果子域为空或无效，访问的 URL 应该是域本身。
 * 示例：
 * - getUrlToVisit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') 返回 'https://a.b.example.com'
 *
 * @param {string} domain - 受信任的域。
 * @param {string} subdomainPrefix - 用户输入的要访问的子域。
 * @returns {string} - 要访问的 URL。
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 清理输入：去除首尾空格
    const cleanDomain = domain.trim();
    const cleanSubdomain = subdomainPrefix.trim();
    
    // 如果子域为空或无效（空字符串或只有空格），直接返回域的HTTPS URL
    if (!cleanSubdomain) {
        return `https://${cleanDomain}`;
    }
    
    // 构建完整的子域URL
    return `https://${cleanSubdomain}.${cleanDomain}`;
}