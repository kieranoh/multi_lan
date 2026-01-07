const crypto = require('crypto');

/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 * 
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // 솔트 생성 (32바이트)
            const salt = crypto.randomBytes(32);
            
            // 비밀번호 해시 생성 (PBKDF2 사용)
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // 솔트와 해시를 결합하여 단일 문자열로 인코딩
                const hash = Buffer.concat([salt, derivedKey]);
                const hashString = hash.toString('base64');
                
                resolve(hashString);
            });
        } catch (error) {
            reject(error);
        }
    });
}