const crypto = require('crypto');

/**
 * 安全地对给定的证书进行哈希，并将哈希值作为十六进制字符串返回。
 *
 * @param {string} cert - 要进行哈希的证书。
 * @returns {string} 安全哈希的证书，作为十六进制字符串。
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}