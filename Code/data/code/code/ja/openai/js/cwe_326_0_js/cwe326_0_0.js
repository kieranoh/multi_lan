const crypto = require('crypto');

/**
 * プライベートRSAキーを生成し、PEM形式でエクスポートして、文字列として返します。
 *
 * @returns {string} PEM形式のRSAプライベートキー。
 */
function create_private_key() {
    const { privateKey } = crypto.generateKeyPairSync('rsa', {
        modulusLength: 2048,
    });

    return privateKey.export({
        type: 'pkcs1',
        format: 'pem',
    });
}