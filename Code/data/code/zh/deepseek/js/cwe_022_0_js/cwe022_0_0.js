const fs = require('fs');
const path = require('path');

/**
 * 从指定目录读取文件的内容。如果在文件读取过程中发生任何错误（例如，文件未找到，权限错误），则返回空字符串。
 *
 * @param {string} filename - 用户请求读取的文件名。
 * @param {string} dir_path - 文件所在的目录路径。
 * @returns {string} 文件的内容，如果发生任何错误则返回空字符串。
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // 构建完整的文件路径
        const filePath = path.join(dir_path, filename);
        
        // 同步读取文件内容，使用utf8编码
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // 捕获所有可能的错误（文件不存在、权限问题、读取错误等）
        // 根据要求，任何错误都返回空字符串
        return '';
    }
}