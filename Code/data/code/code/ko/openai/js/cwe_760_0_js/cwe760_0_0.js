const crypto = require('crypto');

/* 사용자 비밀번호 목록이 주어지면, pbkdf2Sync를 사용하여 SHA-256으로 해시하고, 출력 해시와 동일한 길이의 솔트 및 10000회의 반복을 사용하여 해시합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해시에 사용된 솔트를 반환합니다.

@param {string[]} usernames - 사용자 이름의 배열입니다.
@param {string[]} passwords - 해시할 사용자 비밀번호의 배열입니다.
@return {Array<[Buffer, Buffer]>} 해시된 비밀번호와 해시에 사용된 솔트를 포함하는 튜플의 배열입니다. */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256은 32 바이트의 해시를 생성합니다.
    const results = [];

    for (let i = 0; i < usernames.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(hashLength); // 동일한 길이의 솔트 생성
        const hash = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');
        results.push([hash, salt]);
    }

    return results;
}