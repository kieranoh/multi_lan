/* * 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
 *
 * @returns {string} PEM 형식의 RSA 개인 키. */
function create_private_key() {
    // RSA 키 쌍 생성을 위한 모듈 로드
    const { generateKeyPairSync } = require('crypto');

    // RSA 키 쌍 생성
    const { privateKey } = generateKeyPairSync('rsa', {
        modulusLength: 2048, // 키 크기
    });

    // PEM 형식으로 개인 키 내보내기
    const privateKeyPem = privateKey.export({
        type: 'spki', // 키 유형
        format: 'pem' // 출력 형식
    });

    // PEM 형식의 개인 키 문자열 반환
    return privateKeyPem;
}