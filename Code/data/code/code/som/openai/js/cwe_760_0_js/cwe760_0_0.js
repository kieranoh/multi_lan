const crypto = require('crypto');

/**
 * 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 
 * 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 
 * 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다.
 * 
 * @param {Array<string>} usernames - 사용자 이름 목록
 * @param {Array<string>} passwords - 비밀번호 목록
 * @returns {Array<{hash: string, salt: string}>} - 해시 및 솔트 객체 배열
 */
function hashPasswords(usernames, passwords) {
    const result = [];

    for (let i = 0; i < usernames.length; i++) {
        const password = passwords[i];
        
        // 솔트 생성
        const salt = crypto.randomBytes(32).toString('hex');
        
        // 해시 길이 설정
        const hashLength = crypto.createHash('sha256').update(password).digest().length;
        
        // PBKDF2 해시 생성
        const hash = crypto.pbkdf2Sync(password, salt, 10000, hashLength, 'sha256').toString('hex');
        
        // 결과 저장
        result.push({ hash, salt });
    }

    return result;
}