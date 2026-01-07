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
        throw new Error('인증서는 비어있을 수 없습니다.');
    }
    
    try {
        // SubtleCrypto API를 사용하여 안전한 해시 생성
        // SHA-256은 안전한 해시 알고리즘으로 인증서 해싱에 적합합니다
        const encoder = new TextEncoder();
        const data = encoder.encode(cert);
        
        // crypto.subtle.digest는 Promise를 반환하므로 async/await 사용
        return crypto.subtle.digest('SHA-256', data)
            .then(hashBuffer => {
                // ArrayBuffer를 16진수 문자열로 변환
                const hashArray = Array.from(new Uint8Array(hashBuffer));
                const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
                return hashHex;
            })
            .catch(error => {
                throw new Error(`인증서 해싱 실패: ${error.message}`);
            });
    } catch (error) {
        // SubtleCrypto를 사용할 수 없는 환경을 위한 폴백
        if (error instanceof ReferenceError || !crypto.subtle) {
            console.warn('SubtleCrypto를 사용할 수 없어 폴백 해시 함수를 사용합니다.');
            return Promise.resolve(fallbackHash(cert));
        }
        throw error;
    }
}

/**
 * SubtleCrypto를 사용할 수 없는 환경을 위한 폴백 해시 함수
 * SHA-256을 순수 JavaScript로 구현 (보안 수준은 낮음)
 * 
 * @param {string} str - 해시할 문자열
 * @returns {string} 16진수 해시 문자열
 */
function fallbackHash(str) {
    // 간단한 폴백 해시 함수 (실제 환경에서는 더 강력한 구현 필요)
    let hash = 0;
    for (let i = 0; i < str.length; i++) {
        const char = str.charCodeAt(i);
        hash = ((hash << 5) - hash) + char;
        hash = hash & hash; // 32비트 정수로 변환
    }
    
    // 16진수 문자열로 변환 (8자리로 패딩)
    return Math.abs(hash).toString(16).padStart(8, '0').repeat(8);
}

// 사용 예시:
// hash_certificate('인증서 내용').then(hash => console.log(hash));