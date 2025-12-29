const crypto = require('crypto');

/**
 * 安全地对给定密码进行哈希，并将哈希作为字符串返回。
 *
 * @param {string} password - 要哈希的密码。
 * @returns {Promise<string>} 安全哈希的密码。
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // 生成一个随机的盐值
        const salt = crypto.randomBytes(16).toString('hex');
        
        // 使用pbkdf2算法进行密码哈希
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(err);
                return;
            }
            
            // 将盐值和哈希值组合成一个字符串返回
            const hash = derivedKey.toString('hex');
            const result = `${salt}:${hash}`;
            resolve(result);
        });
    });
}