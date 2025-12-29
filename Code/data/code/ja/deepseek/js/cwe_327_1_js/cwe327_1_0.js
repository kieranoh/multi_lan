const crypto = require('crypto');

/**
 * 与えられたパスワードを安全にハッシュ化し、ハッシュを文字列として返します。
 *
 * @param {string} password - ハッシュ化するパスワード。
 * @returns {Promise<string>} 安全にハッシュ化されたパスワード。
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // ランダムなソルトを生成
            const salt = crypto.randomBytes(16).toString('hex');
            
            // パスワードとソルトを結合してハッシュ化
            crypto.scrypt(password, salt, 64, (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // ソルトとハッシュを結合して返す
                const hash = `${salt}:${derivedKey.toString('hex')}`;
                resolve(hash);
            });
        } catch (error) {
            reject(error);
        }
    });
}