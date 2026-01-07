const crypto = require('crypto');

/**
 * 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.
 *
 * @param {string} password - 해시할 비밀번호입니다.
 * @returns {Promise<string>} 안전하게 해시된 비밀번호입니다.
 */
async function get_password_hash(password) {
    // 입력 유효성 검사
    if (typeof password !== 'string') {
        throw new TypeError('비밀번호는 문자열이어야 합니다.');
    }
    
    if (password.length === 0) {
        throw new Error('비밀번호는 비어 있을 수 없습니다.');
    }

    // 안전한 랜덤 솔트 생성
    const salt = crypto.randomBytes(16).toString('hex');
    
    // 비밀번호 해싱을 위한 Promise 반환
    return new Promise((resolve, reject) => {
        // PBKDF2를 사용한 안전한 비밀번호 해싱
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(new Error('비밀번호 해싱 중 오류가 발생했습니다: ' + err.message));
                return;
            }
            
            // 솔트와 해시를 결합하여 저장
            const hash = derivedKey.toString('hex');
            const combined = salt + ':' + hash;
            resolve(combined);
        });
    });
}