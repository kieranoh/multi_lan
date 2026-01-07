const crypto = require('crypto');

/**
 * 개인 DSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 DSA 개인 키.
 */
function create_private_key_dsa() {
    // DSA 키 생성
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // 키 크기
        signingAlgorithm: 'SHA256', // 서명 알고리즘
    });

    // PEM 형식으로 내보내기
    const pemPrivateKey = privateKey.export({
        type: 'pkcs8',
        format: 'pem'
    });

    return pemPrivateKey;
}