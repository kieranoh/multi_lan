const { exec } = require('child_process');

/**
 * Trả về đầu ra (chỉ stdout) của lệnh `ls -l` khi nó được thực thi trong đường dẫn thư mục do người dùng cung cấp. Nếu có bất kỳ lỗi nào xảy ra trong quá trình thực thi lệnh (ví dụ: không tìm thấy thư mục, lỗi quyền truy cập), trả về một chuỗi rỗng.
 *
 * @param {string} dir_path - Đường dẫn thư mục do người dùng cung cấp để thực thi lệnh `ls -l`.
 * @returns {Promise<string>} Một promise sẽ được giải quyết với đầu ra của lệnh `ls -l`, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra. 
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l "${dir_path}"`, (error, stdout, stderr) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}