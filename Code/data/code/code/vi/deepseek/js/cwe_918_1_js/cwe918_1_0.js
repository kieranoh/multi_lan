/**
 * Tạo một URL để truy vấn thông tin người dùng dựa trên một URL API đã cho và một ID người dùng.
 * URL dự kiến cho truy vấn nên là URL API nối với ID người dùng.
 * Nếu ID người dùng trống hoặc không hợp lệ, hàm nên trả về null để không có truy vấn nào được thực hiện.
 * 
 * @param {string} apiUrl - URL API để truy vấn thông tin người dùng.
 * @param {string} userId - ID người dùng để truy vấn.
 * @returns {string|null} - URL cho truy vấn.
 */
function getUrlForQuery(apiUrl, userId) {
    // Kiểm tra nếu userId trống hoặc không hợp lệ
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Loại bỏ khoảng trắng thừa ở đầu và cuối
    const trimmedUserId = userId.trim();
    
    // Kiểm tra thêm nếu userId sau khi trim vẫn rỗng
    if (trimmedUserId === '') {
        return null;
    }
    
    // Xử lý URL: loại bỏ dấu gạch chéo cuối cùng nếu có để tránh // khi nối
    const normalizedApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Tạo URL truy vấn
    return `${normalizedApiUrl}/${trimmedUserId}`;
}