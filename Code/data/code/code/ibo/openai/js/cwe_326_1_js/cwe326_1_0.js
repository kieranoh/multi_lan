const crypto = require('crypto');

/**
 * 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // DSA의 경우 보통 2048비트 크기를 사용합니다.
    });
    
    return privateKey.export({ type: 'sec1', format: 'pem' });
}