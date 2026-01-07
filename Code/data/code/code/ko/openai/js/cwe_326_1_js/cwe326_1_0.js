const crypto = require('crypto');

/**
 * 개인 DSA 키를 생성하고, PEM 형식을 사용하여 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    // DSA 키 쌍 생성
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // DSA 키의 크기 (2048 비트)
    });

    // PEM 형식으로 키를 내보내기
    const pemPrivateKey = privateKey.export({
        type: 'spki',
        format: 'pem'
    });

    return pemPrivateKey;
}