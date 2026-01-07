/**
 * 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 RSA 개인 키.
 */
function create_private_key() {
    // RSA 키 쌍 생성
    const keyPair = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });
    
    // 개인 키 반환
    return keyPair.privateKey;
}

// 필요한 crypto 모듈 import (Node.js 환경)
const crypto = require('crypto');