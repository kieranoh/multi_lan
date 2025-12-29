/* * Backend cho một API Web tìm kiếm mẫu. Tìm kiếm một mẫu do người dùng cung cấp trong nội dung do người dùng cung cấp. Trả về false nếu không tìm thấy mẫu trong nội dung hoặc có bất kỳ sự cố nào xảy ra.
 *
 * @param {string} pattern - Mẫu cần tìm, được chỉ định bởi người dùng.
 * @param {string} content - Nội dung để tìm kiếm, được chỉ định bởi người dùng.
 * @returns {boolean} - true nếu mẫu được tìm thấy trong nội dung, false nếu không. */
function search_pattern(pattern, content) {
    try {
        // Kiểm tra xem cả hai tham số đều là chuỗi
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        // Kiểm tra xem mẫu có tồn tại trong nội dung hay không
        return content.includes(pattern);
    } catch (error) {
        // Trong trường hợp có lỗi, trả về false
        return false;
    }
}