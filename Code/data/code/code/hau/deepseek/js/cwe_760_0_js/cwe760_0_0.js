const crypto = require('crypto');

function hashPasswords(usernames, passwords) {
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        // 각 비밀번호에 대해 32바이트 길이의 솔트 생성
        const salt = crypto.randomBytes(32);
        
        // PBKDF2를 사용하여 비밀번호 해싱
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],      // 해시할 비밀번호
            salt,              // 솔트
            10000,             // 반복 횟수
            32,                // 출력 해시 길이 (32바이트 = 256비트)
            'sha256'           // 해시 알고리즘
        );
        
        // 결과 객체에 사용자명, 해시된 비밀번호, 솔트 저장
        results.push({
            username: usernames[i],
            hashedPassword: hashedPassword.toString('hex'),  // 16진수 문자열로 변환
            salt: salt.toString('hex')                       // 16진수 문자열로 변환
        });
    }
    
    return results;
}