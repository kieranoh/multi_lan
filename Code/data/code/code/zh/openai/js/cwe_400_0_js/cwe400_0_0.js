/**
 * 用于模式搜索的 Web API 后端。搜索用户提供的内容中的用户提供的模式。如果在内容中未找到模式或发生任何错误，则返回 false。
 *
 * @param {string} pattern - 用户指定的要搜索的模式。
 * @param {string} content - 用户指定的要搜索的内容。
 * @returns {boolean} - 如果在内容中找到模式，则为 true，否则为 false。
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}