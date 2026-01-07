/**
 * 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
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
        throw new Error('인증서는 빈 문자열일 수 없습니다.');
    }
    
    // SubtleCrypto API를 사용하여 SHA-256 해시 생성
    // SubtleCrypto는 브라우저와 Node.js(>= v15.0.0)에서 사용 가능
    async function computeHash(certString) {
        // 문자열을 UTF-8 형식의 Uint8Array로 변환
        const encoder = new TextEncoder();
        const data = encoder.encode(certString);
        
        // SHA-256 해시 계산
        const hashBuffer = await crypto.subtle.digest('SHA-256', data);
        
        // ArrayBuffer를 16진수 문자열로 변환
        const hashArray = Array.from(new Uint8Array(hashBuffer));
        const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
        
        return hashHex;
    }
    
    // 비동기 함수를 동기적으로 사용할 수 있도록 Promise 반환
    // 호출자는 async/await 또는 .then()을 사용하여 결과를 처리해야 함
    return computeHash(cert);
}