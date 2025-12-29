const crypto = require('crypto');

/**
 * プライベートDSAキーを生成し、PEM形式でエクスポートして文字列として返します。
 *
 * @returns {string} PEM形式のDSAプライベートキー。
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = crypto;
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // DSA用のビット数、2048は安全な長さ
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