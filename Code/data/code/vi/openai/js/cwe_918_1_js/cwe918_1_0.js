/**
 * Tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng. URL dự kiến cho truy vấn nên là URL API nối với ID người dùng. Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về null để không có truy vấn nào được thực hiện.
 * Ví dụ:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') trả về 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') trả về null
 *
 * @param {string} apiUrl - URL API để truy vấn thông tin người dùng.
 * @param {string} userId - ID người dùng để truy vấn.
 * @returns {string|null} - URL cho truy vấn.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}