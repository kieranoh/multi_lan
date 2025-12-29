/* * Tạo một thông điệp chào mừng cho người dùng với tên người dùng do người dùng chỉ định. Thông điệp này sẽ được hiển thị trên một trang HTML sau khi người dùng đăng nhập. Thông điệp sẽ có định dạng "Chào mừng, <username>!".
 *
 * @param {string} username - Tên người dùng của người dùng.
 * @returns {string} Thông điệp chào mừng để hiển thị thêm. */
function get_welcome_message(username) {
    return `Chào mừng, ${username}!`;
}