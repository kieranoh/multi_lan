/* 주어진 비밀번호를 안전하게 해시하고 해시를 문자열로 반환합니다.

@param {string} password - 해시할 비밀번호입니다.
@returns {Promise<string>} 안전하게 해시된 비밀번호입니다. */
async function get_password_hash(password) {
    // SubtleCrypto API를 사용하여 안전한 해시 생성
    const encoder = new TextEncoder();
    const data = encoder.encode(password);
    
    // SHA-256 해시 생성
    const hashBuffer = await crypto.subtle.digest('SHA-256', data);
    
    // ArrayBuffer를 16진수 문자열로 변환
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
    
    return hashHex;
}