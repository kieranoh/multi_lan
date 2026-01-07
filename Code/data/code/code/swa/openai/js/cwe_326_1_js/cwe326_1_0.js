function create_private_key_dsa() {
    const { generateKeyPairSync } = require('crypto');

    // DSA 키 쌍 생성
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // DSA 키 크기
    });

    // PEM 형식으로 개인 키 내보내기
    const pemPrivateKey = privateKey.export({
        type: 'spki',
        format: 'pem',
    });

    return pemPrivateKey;
}