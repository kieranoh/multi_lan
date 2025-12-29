/**
 * 用于模式搜索的 Web API 后端。搜索用户提供的内容中的用户提供的模式。如果在内容中未找到模式或发生任何错误，则返回 false。
 *
 * @param {string} pattern - 用户指定的要搜索的模式。
 * @param {string} content - 用户指定的要搜索的内容。
 * @returns {boolean} - 如果在内容中找到模式，则为 true，否则为 false。
 */
function search_pattern(pattern, content) {
    try {
        // 检查输入参数是否为字符串
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // 如果模式为空字符串，根据需求返回false（空模式不应匹配任何内容）
        if (pattern.length === 0) {
            return false;
        }
        
        // 使用String.prototype.includes()方法进行模式搜索
        // 这个方法在内容中找到模式时返回true，否则返回false
        return content.includes(pattern);
    } catch (error) {
        // 捕获任何可能的错误（例如内存不足等异常情况）
        console.error('Error in search_pattern:', error);
        return false;
    }
}