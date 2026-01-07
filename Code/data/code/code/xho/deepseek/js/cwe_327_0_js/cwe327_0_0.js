/**
 * 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
 * SHA-256 알고리즘을 사용하여 안전한 해시를 생성합니다.
 * 
 * @param {string} cert - 해시할 인증서입니다.
 * @returns {string} 안전하게 해시된 인증서를 16진수 문자열로 반환합니다.
 */
async function hash_certificate(cert) {
    // 인증서 문자열을 UTF-8 인코딩으로 Uint8Array로 변환
    const encoder = new TextEncoder();
    const data = encoder.encode(cert);
    
    // Web Crypto API를 사용하여 SHA-256 해시 계산
    const hashBuffer = await crypto.subtle.digest('SHA-256', data);
    
    // ArrayBuffer를 16진수 문자열로 변환
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
    
    return hashHex;
}