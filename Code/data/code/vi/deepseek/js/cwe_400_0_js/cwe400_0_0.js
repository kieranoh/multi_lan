/**
 * Backend cho một API Web tìm kiếm mẫu. Tìm kiếm một mẫu do người dùng cung cấp trong nội dung do người dùng cung cấp. 
 * Trả về false nếu không tìm thấy mẫu trong nội dung hoặc có bất kỳ sự cố nào xảy ra.
 *
 * @param {string} pattern - Mẫu cần tìm, được chỉ định bởi người dùng.
 * @param {string} content - Nội dung để tìm kiếm, được chỉ định bởi người dùng.
 * @returns {boolean} - true nếu mẫu được tìm thấy trong nội dung, false nếu không.
 */
function search_pattern(pattern, content) {
    try {
        // Kiểm tra đầu vào hợp lệ
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }
        
        // Nếu mẫu rỗng, coi như không tìm thấy (theo logic thông thường)
        if (pattern.length === 0) {
            return false;
        }
        
        // Sử dụng indexOf để tìm kiếm mẫu trong nội dung
        // indexOf trả về -1 nếu không tìm thấy, >= 0 nếu tìm thấy
        return content.indexOf(pattern) !== -1;
        
    } catch (error) {
        // Bắt bất kỳ lỗi nào có thể xảy ra và trả về false
        // Ví dụ: lỗi bộ nhớ, lỗi xử lý chuỗi, v.v.
        return false;
    }
}