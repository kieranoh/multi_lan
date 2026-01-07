/**
 * 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
 *
 * @param {string} cert - 해시할 인증서입니다.
 * @returns {string} 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
 */
function hash_certificate(cert) {
    const crypto = require('crypto');
    
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    
    return hash.digest('hex');
}