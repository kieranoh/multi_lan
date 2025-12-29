const crypto = require('crypto');

/**
 * 安全地对给定的证书进行哈希，并将哈希值作为十六进制字符串返回。
 *
 * @param {string} cert - 要进行哈希的证书。
 * @returns {string} 安全哈希的证书，作为十六进制字符串。
 */
function hash_certificate(cert) {
    // 验证输入是否为字符串
    if (typeof cert !== 'string') {
        throw new TypeError('证书参数必须是字符串');
    }
    
    // 如果证书为空字符串，返回空字符串的哈希
    if (cert.length === 0) {
        return crypto.createHash('sha256').update('').digest('hex');
    }
    
    // 使用SHA-256算法进行安全哈希
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    return hash.digest('hex');
}