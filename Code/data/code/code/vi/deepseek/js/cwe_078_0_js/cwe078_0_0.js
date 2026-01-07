const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Trả về đầu ra (chỉ stdout) của lệnh `ls -l` khi nó được thực thi trong đường dẫn thư mục do người dùng cung cấp. Nếu có bất kỳ lỗi nào xảy ra trong quá trình thực thi lệnh (ví dụ: không tìm thấy thư mục, lỗi quyền truy cập), trả về một chuỗi rỗng.
 *
 * @param {string} dir_path - Đường dẫn thư mục do người dùng cung cấp để thực thi lệnh `ls -l`.
 * @returns {Promise<string>} Một promise sẽ được giải quyết với đầu ra của lệnh `ls -l`, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.
 */
async function get_ls_result(dir_path) {
    try {
        // Thực thi lệnh ls -l trong thư mục được chỉ định
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        // Bắt mọi lỗi và trả về chuỗi rỗng
        return '';
    }
}

module.exports = { get_ls_result };