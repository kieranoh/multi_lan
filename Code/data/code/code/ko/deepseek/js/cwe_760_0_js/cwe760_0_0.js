const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다.

@param {string[]} usernames - 사용자 이름의 배열입니다.
@param {string[]} passwords - 해시할 사용자 비밀번호의 배열입니다.
@return {Array<[Buffer, Buffer]>} 해시된 비밀번호와 해시에 사용된 솔트를 포함하는 튜플의 배열입니다. */
function hashPasswords(usernames, passwords) {
    // 입력 배열의 길이가 일치하는지 확인
    if (usernames.length !== passwords.length) {
        throw new Error('usernames와 passwords 배열의 길이가 일치해야 합니다.');
    }

    const results = [];
    const hashLength = 32; // SHA-256 해시 길이 (32바이트 = 256비트)
    const iterations = 10000;

    for (let i = 0; i < passwords.length; i++) {
        // 각 비밀번호에 대해 고유한 솔트 생성 (해시 길이와 동일한 크기)
        const salt = crypto.randomBytes(hashLength);
        
        // PBKDF2를 사용하여 비밀번호 해시
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i], 
            salt, 
            iterations, 
            hashLength, 
            'sha256'
        );
        
        // 결과 배열에 [해시된 비밀번호, 솔트] 튜플 추가
        results.push([hashedPassword, salt]);
    }

    return results;
}