const crypto = require('crypto');

/**
 * 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    // DSA 키 파라미터 생성 (2048비트, 서브프라임 256비트)
    const keyParams = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048,
        divisorLength: 256,
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });
    
    // 개인 키만 반환
    return keyParams.privateKey;
}