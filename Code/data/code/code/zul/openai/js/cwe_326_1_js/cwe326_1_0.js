/**
 * 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = require('crypto');

    // DSA 키 쌍 생성
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // 키 길이 설정
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });

    return privateKey; // PEM 형식의 DSA 개인 키 반환
}