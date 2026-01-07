async function get_password_hash(password) {
    // 1. 비밀번호를 UTF-8 형식으로 인코딩
    const encoder = new TextEncoder();
    const passwordData = encoder.encode(password);
    
    // 2. 랜덤 솔트 생성 (16바이트)
    const salt = crypto.getRandomValues(new Uint8Array(16));
    
    // 3. 솔트와 비밀번호를 결합
    const combinedData = new Uint8Array(passwordData.length + salt.length);
    combinedData.set(passwordData);
    combinedData.set(salt, passwordData.length);
    
    // 4. SHA-256 해시 적용
    const hashBuffer = await crypto.subtle.digest('SHA-256', combinedData);
    
    // 5. 해시와 솔트를 결합하여 저장용 문자열 생성
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const saltArray = Array.from(salt);
    
    // 6. 해시와 솔트를 Base64 문자열로 변환
    const hashString = btoa(String.fromCharCode.apply(null, hashArray));
    const saltString = btoa(String.fromCharCode.apply(null, saltArray));
    
    // 7. 형식: "해시:솔트" (나중에 검증을 위해 함께 저장)
    return `${hashString}:${saltString}`;
}