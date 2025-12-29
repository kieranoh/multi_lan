const crypto = require('crypto');

/**
 * プライベートDSAキーを生成し、PEM形式でエクスポートして文字列として返します。
 *
 * @returns {string} PEM形式のDSAプライベートキー。
 */
function create_private_key_dsa() {
    // DSAキーペアを生成するためのパラメータを設定
    // 2048ビットのキー長と、SHA-256ハッシュに適した256ビットのサブグループサイズを使用
    const keyPair = crypto.generateKeyPairSync('dsa', {
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
    
    // プライベートキーをPEM形式で返す
    return keyPair.privateKey;
}