/**
 * 根据给定的 API URL 和用户 ID 生成查询用户信息的 URL。预期的查询 URL 应该是 API URL 与用户 ID 的连接。如果用户 ID 为空或无效，函数应返回 null，以便不进行查询。
 * 示例：
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') 返回 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') 返回 null
 *
 * @param {string} apiUrl - 查询用户信息的 API URL。
 * @param {string} userId - 要查询的用户 ID。
 * @returns {string|null} - 查询的 URL。
 */
function getUrlForQuery(apiUrl, userId) {
    // 检查 userId 是否为空或无效
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // 移除 apiUrl 末尾可能存在的斜杠，并确保 userId 被正确附加
    const trimmedApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    const trimmedUserId = userId.trim();
    
    // 返回拼接后的 URL
    return `${trimmedApiUrl}/${trimmedUserId}`;
}