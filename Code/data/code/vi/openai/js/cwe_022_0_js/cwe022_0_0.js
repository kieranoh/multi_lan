const fs = require('fs');
const path = require('path');

/**
 * Đọc nội dung của một tệp từ một thư mục được chỉ định. Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: tệp không tìm thấy, lỗi quyền truy cập), trả về một chuỗi rỗng.
 *
 * @param {string} filename - Tên của tệp cần đọc, được yêu cầu bởi người dùng.
 * @param {string} dir_path - Đường dẫn thư mục nơi tệp được lưu trữ.
 * @returns {string} Nội dung của tệp, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra. */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}