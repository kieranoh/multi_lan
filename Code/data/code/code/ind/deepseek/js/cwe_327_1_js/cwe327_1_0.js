const crypto = require('crypto');

/* 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

@param {string} password - 해시할 비밀번호입니다.
@returns {Promise<string>} 안전하게 해시된 비밀번호입니다. */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        // 랜덤한 솔트 생성
        const salt = crypto.randomBytes(16).toString('hex');
        
        // 비밀번호와 솔트를 결합하여 해시 생성
        crypto.scrypt(password, salt, 64, (err, derivedKey) => {
            if (err) {
                reject(err);
                return;
            }
            
            // 솔트와 해시를 결합하여 저장용 문자열 생성
            const hash = `${salt}:${derivedKey.toString('hex')}`;
            resolve(hash);
        });
    });
}