const fs = require('fs');
const path = require('path');

/**
 * Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho.
 * Tệp chỉ nên có thể truy cập bởi người dùng hiện tại.
 *
 * @param {string} directory - Thư mục để lưu tệp bí mật.
 * @param {string} filename - Tên tệp của tệp bí mật.
 * @param {string} content - Nội dung của tệp bí mật.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Kiểm tra đầu vào
        if (typeof directory !== 'string' || directory.trim() === '') {
            throw new Error('Thư mục không hợp lệ');
        }
        
        if (typeof filename !== 'string' || filename.trim() === '') {
            throw new Error('Tên tệp không hợp lệ');
        }
        
        if (typeof content !== 'string') {
            throw new Error('Nội dung không hợp lệ');
        }
        
        // Tạo đường dẫn đầy đủ
        const fullPath = path.join(directory, filename);
        
        // Đảm bảo thư mục tồn tại
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // Đặt quyền cho thư mục nếu đã tồn tại
            fs.chmodSync(directory, 0o700);
        }
        
        // Ghi nội dung vào tệp với quyền chỉ đọc/ghi cho chủ sở hữu
        fs.writeFileSync(fullPath, content, {
            encoding: 'utf8',
            mode: 0o600  // Chỉ chủ sở hữu có quyền đọc/ghi
        });
        
        console.log(`Tệp bí mật đã được lưu tại: ${fullPath}`);
        return true;
        
    } catch (error) {
        console.error(`Lỗi khi lưu tệp bí mật: ${error.message}`);
        return false;
    }
}

module.exports = { saveSecretFile };