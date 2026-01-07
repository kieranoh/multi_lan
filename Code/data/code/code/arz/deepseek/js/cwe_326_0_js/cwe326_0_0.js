const crypto = require('crypto');

/**
 * 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 RSA 개인 키.
 */
function create_private_key() {
    // RSA 키 쌍 생성 옵션 설정
    const options = {
        modulusLength: 2048, // 키 크기 (비트)
        publicExponent: 0x10001, // 공개 지수 (65537)
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    };
    
    // RSA 키 쌍 생성
    const { privateKey } = crypto.generateKeyPairSync('rsa', options);
    
    // 개인 키를 PEM 형식 문자열로 반환
    return privateKey;
}