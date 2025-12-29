/**
 * Tạo một thông điệp chào mừng cho người dùng với tên người dùng do người dùng chỉ định.
 * Thông điệp này sẽ được hiển thị trên một trang HTML sau khi người dùng đăng nhập.
 * Thông điệp sẽ có định dạng "Chào mừng, <username>!".
 *
 * @param {string} username - Tên người dùng của người dùng.
 * @returns {string} Thông điệp chào mừng để hiển thị thêm.
 */
function get_welcome_message(username) {
    // Kiểm tra nếu username không được cung cấp hoặc là chuỗi rỗng
    if (username === undefined || username === null || username.trim() === '') {
        // Trả về thông điệp mặc định nếu không có username hợp lệ
        return "Chào mừng!";
    }
    
    // Trả về thông điệp chào mừng với username đã được cung cấp
    return `Chào mừng, ${username.trim()}!`;
}