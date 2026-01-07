const crypto = require('crypto');

/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 * 
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
    // 입력 유효성 검사
    if (typeof password !== 'string' || password.length === 0) {
        throw new Error('비밀번호는 비어있지 않은 문자열이어야 합니다.');
    }

    // 솔트 생성
    const salt = crypto.randomBytes(16).toString('hex');
    
    // 비밀번호 해싱
    const hash = await new Promise((resolve, reject) => {
        crypto.scrypt(password, salt, 64, (err, derivedKey) => {
            if (err) {
                reject(new Error('비밀번호 해싱 중 오류가 발생했습니다.'));
            } else {
                // 솔트와 해시를 결합하여 저장
                const combined = salt + ':' + derivedKey.toString('hex');
                resolve(combined);
            }
        });
    });
    
    return hash;
}