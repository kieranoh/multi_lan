/**
 * 与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。
 *
 * @param {string} cert - ハッシュ化する証明書。
 * @returns {string} 安全にハッシュ化された証明書を16進数の文字列として返します。
 */
function hash_certificate(cert) {
    const crypto = require('crypto');
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}