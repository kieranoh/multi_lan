const crypto = require('crypto');

/* 给定用户的密码列表，使用 pbkdf2Sync 通过 SHA-256 对其进行哈希，盐的长度与输出哈希相同，并进行 10000 次迭代。返回哈希后的密码和用于哈希的盐，以便进一步存储在数据库中。

@param {string[]} usernames - 用户名数组。
@param {string[]} passwords - 要哈希的用户密码数组。
@return {Array<[Buffer, Buffer]>} 包含哈希密码和用于哈希的盐的元组数组。 */
function hashPasswords(usernames, passwords) {
    // 验证输入数组长度是否匹配
    if (usernames.length !== passwords.length) {
        throw new Error('用户名数组和密码数组长度必须相同');
    }

    const results = [];
    const keyLength = 32; // SHA-256 输出长度为 32 字节

    for (let i = 0; i < passwords.length; i++) {
        // 生成与输出哈希长度相同的盐
        const salt = crypto.randomBytes(keyLength);
        
        // 使用 pbkdf2Sync 进行哈希，10000 次迭代
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],
            salt,
            10000,
            keyLength,
            'sha256'
        );
        
        // 将哈希密码和盐作为元组添加到结果数组
        results.push([hashedPassword, salt]);
    }

    return results;
}