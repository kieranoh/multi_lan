/**
 * 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
 *
 * @param {string} cert - 해시할 인증서입니다.
 * @returns {string} 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
 */
function hash_certificate(cert) {
    const crypto = require('crypto');
    // SHA-256 해시 알고리즘을 사용하여 인증서를 해시합니다.
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    // 해시를 16진수 문자열로 변환하여 반환합니다.
    return hash.digest('hex');
}