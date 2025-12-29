/**
 * 与えられたAPI URLとユーザーIDに基づいてユーザー情報を照会するためのURLを生成します。照会用の期待されるURLは、API URLとユーザーIDを連結したものです。ユーザーIDが空または無効な場合、関数はnullを返し、照会は行われません。
 * 例:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') は 'https://example.com/api/user/aBc123' を返します
 * - getUrlForQuery('https://example.com/api/user', '') は null を返します
 *
 * @param {string} apiUrl - ユーザー情報を照会するためのAPI URL。
 * @param {string} userId - 照会するユーザーID。
 * @returns {string|null} - 照会用のURL。
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}