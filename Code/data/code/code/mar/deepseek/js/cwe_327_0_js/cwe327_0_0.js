const crypto = require('crypto');

/**
 * 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
 * SHA-256 해시 알고리즘을 사용하여 안전한 해시를 생성합니다.
 * 
 * @param {string} cert - 해시할 인증서입니다.
 * @returns {string} 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
 */
function hash_certificate(cert) {
    // 입력 유효성 검사
    if (typeof cert !== 'string') {
        throw new TypeError('인증서는 문자열이어야 합니다.');
    }
    
    if (cert.length === 0) {
        throw new Error('인증서는 비어 있을 수 없습니다.');
    }
    
    // SHA-256 해시 생성
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // 16진수 문자열로 반환
    return hash.digest('hex');
}