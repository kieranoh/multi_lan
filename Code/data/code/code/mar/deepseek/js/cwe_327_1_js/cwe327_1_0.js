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
            // 1. 솔트 생성
            const salt = crypto.randomBytes(16).toString('hex');
            
            // 2. 비밀번호 해싱
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // 3. 솔트와 해시를 결합하여 저장용 문자열 생성
                const hash = derivedKey.toString('hex');
                const combined = `${salt}:${hash}`;
                
                resolve(combined);
            });
        } catch (error) {
            reject(error);
        }
    });
}