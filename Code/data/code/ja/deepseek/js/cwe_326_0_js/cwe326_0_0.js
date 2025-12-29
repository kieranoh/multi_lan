const crypto = require('crypto');

/**
 * プライベートRSAキーを生成し、PEM形式でエクスポートして、文字列として返します。
 *
 * @returns {string} PEM形式のRSAプライベートキー。
 */
function create_private_key() {
    // 2048ビットのRSAキーペアを生成
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
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
    
    return privateKey;
}