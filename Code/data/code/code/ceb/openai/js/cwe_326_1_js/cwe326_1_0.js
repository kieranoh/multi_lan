const crypto = require('crypto');

/**
 * 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    // DSA 키 쌍을 생성합니다.
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // 2048 비트 길이의 모듈러 수
        publicKeyEncoding: {
            type: 'spki', // 공개 키 인코딩 형식
            format: 'pem' // PEM 형식
        },
        privateKeyEncoding: {
            type: 'pkcs8', // 개인 키 인코딩 형식
            format: 'pem' // PEM 형식
        }
    });

    // 개인 키를 문자열로 반환합니다.
    return privateKey;
}