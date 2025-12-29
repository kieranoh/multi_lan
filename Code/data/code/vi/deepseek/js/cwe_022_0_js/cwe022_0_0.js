const fs = require('fs');
const path = require('path');

/**
 * Đọc nội dung của một tệp từ một thư mục được chỉ định. Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: tệp không tìm thấy, lỗi quyền truy cập), trả về một chuỗi rỗng.
 *
 * @param {string} filename - Tên của tệp cần đọc, được yêu cầu bởi người dùng.
 * @param {string} dir_path - Đường dẫn thư mục nơi tệp được lưu trữ.
 * @returns {string} Nội dung của tệp, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.
 */
function read_file_from_dir(filename, dir_path) {
    // Kiểm tra đầu vào hợp lệ
    if (typeof filename !== 'string' || typeof dir_path !== 'string') {
        return '';
    }
    
    // Xử lý trường hợp chuỗi rỗng
    if (filename.trim() === '' || dir_path.trim() === '') {
        return '';
    }
    
    try {
        // Xây dựng đường dẫn đầy đủ đến tệp
        const fullPath = path.join(dir_path, filename);
        
        // Kiểm tra xem đường dẫn có hợp lệ không (ngăn chặn các cuộc tấn công đường dẫn)
        const resolvedPath = path.resolve(dir_path, filename);
        const resolvedDir = path.resolve(dir_path);
        
        // Đảm bảo rằng đường dẫn giải quyết vẫn nằm trong thư mục được chỉ định
        if (!resolvedPath.startsWith(resolvedDir)) {
            return '';
        }
        
        // Đọc tệp đồng bộ với mã hóa UTF-8
        const content = fs.readFileSync(fullPath, 'utf8');
        return content;
    } catch (error) {
        // Bắt tất cả các loại lỗi: tệp không tìm thấy, lỗi quyền, v.v.
        return '';
    }
}

module.exports = { read_file_from_dir };