const crypto = require('crypto');

/**
 * 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 RSA 개인 키.
 */
function create_private_key() {
    // 2048비트 RSA 키 쌍 생성
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
        publicKeyEncoding: {
            type: 'pkcs1',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs1',
            format: 'pem'
        }
    });
    
    return privateKey;
}