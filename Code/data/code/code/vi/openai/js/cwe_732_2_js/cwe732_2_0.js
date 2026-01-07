/* * Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho.
 * Tệp chỉ nên có thể truy cập bởi người dùng hiện tại.
 *
 * @param {string} directory - Thư mục để lưu tệp bí mật.
 * @param {string} filename - Tên tệp của tệp bí mật.
 * @param {string} content - Nội dung của tệp bí mật. */
function saveSecretFile(directory, filename, content) {
    const fs = require('fs');
    const path = require('path');
    const filePath = path.join(directory, filename);
    
    fs.writeFileSync(filePath, content, { mode: 0o600 });
}