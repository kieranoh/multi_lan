const fs = require('fs');
const path = require('path');

/**
 * 将秘密文件保存到指定目录，使用指定的文件名和内容。
 * 该文件应仅对当前用户可访问。
 *
 * @param {string} directory - 保存秘密文件的目录。
 * @param {string} filename - 秘密文件的文件名。
 * @param {string} content - 秘密文件的内容。
 */
function saveSecretFile(directory, filename, content) {
    // 确保目录存在
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // 构建完整的文件路径
    const filePath = path.join(directory, filename);

    // 写入文件内容，设置权限为仅当前用户可读写（0o600）
    fs.writeFileSync(filePath, content, {
        encoding: 'utf8',
        mode: 0o600  // 仅所有者可读写
    });
}