const crypto = require('crypto');

/**
 * 与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。
 *
 * @param {string} cert - ハッシュ化する証明書。
 * @returns {string} 安全にハッシュ化された証明書を16進数の文字列として返します。
 */
function hash_certificate(cert) {
    // 入力検証
    if (typeof cert !== 'string') {
        throw new TypeError('証明書は文字列である必要があります');
    }
    
    if (cert.trim().length === 0) {
        throw new Error('証明書は空であってはいけません');
    }
    
    // SHA-256ハッシュを使用して証明書をハッシュ化
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // 16進数の文字列として返す
    return hash.digest('hex');
}