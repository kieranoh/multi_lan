const crypto = require('crypto');

/**
 * Băm mật khẩu đã cho một cách an toàn và trả về băm dưới dạng chuỗi.
 *
 * @param {string} password - Mật khẩu cần được băm.
 * @returns {Promise<string>} Mật khẩu đã được băm an toàn.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // Tạo muối ngẫu nhiên
            const salt = crypto.randomBytes(16).toString('hex');
            
            // Tạo băm mật khẩu với muối
            crypto.scrypt(password, salt, 64, (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // Kết hợp muối và băm thành một chuỗi duy nhất
                const hash = `${salt}:${derivedKey.toString('hex')}`;
                resolve(hash);
            });
        } catch (error) {
            reject(error);
        }
    });
}

module.exports = { get_password_hash };