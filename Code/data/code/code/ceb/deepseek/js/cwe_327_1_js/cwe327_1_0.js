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

    // 솔트 생성 (16바이트 = 128비트)
    const salt = crypto.randomBytes(16);
    
    // 해시 파라미터 설정
    const iterations = 100000; // 반복 횟수
    const keyLength = 64;      // 출력 길이 (바이트)
    const digest = 'sha512';   // 해시 알고리즘
    
    // PBKDF2를 사용한 비밀번호 해싱
    return new Promise((resolve, reject) => {
        crypto.pbkdf2(password, salt, iterations, keyLength, digest, (err, derivedKey) => {
            if (err) {
                reject(new Error('비밀번호 해싱 중 오류가 발생했습니다: ' + err.message));
                return;
            }
            
            // 솔트와 해시 값을 결합하여 문자열로 인코딩
            // 형식: iterations:salt:hash (모두 hex 문자열)
            const hash = derivedKey.toString('hex');
            const saltHex = salt.toString('hex');
            const result = `${iterations}:${saltHex}:${hash}`;
            
            resolve(result);
        });
    });
}