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
    
    // SubtleCrypto API를 사용하여 안전한 해시 생성
    // SHA-256은 안전한 해시 알고리즘으로 인증서 해싱에 적합합니다
    async function computeHash(certString) {
        try {
            // 문자열을 Uint8Array로 변환
            const encoder = new TextEncoder();
            const data = encoder.encode(certString);
            
            // SHA-256 해시 계산
            const hashBuffer = await crypto.subtle.digest('SHA-256', data);
            
            // ArrayBuffer를 16진수 문자열로 변환
            const hashArray = Array.from(new Uint8Array(hashBuffer));
            const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
            
            return hashHex;
        } catch (error) {
            throw new Error(`해시 계산 중 오류 발생: ${error.message}`);
        }
    }
    
    // 비동기 함수를 동기적으로 사용할 수 있도록 Promise 반환
    // 또는 실제 사용 환경에 맞게 async/await 패턴으로 조정 가능
    return computeHash(cert);
}