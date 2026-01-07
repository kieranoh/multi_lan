function hash_certificate(cert) {
  // 입력 유효성 검사
  if (typeof cert !== 'string' || cert.trim() === '') {
    throw new Error('인증서는 비어있지 않은 문자열이어야 합니다.');
  }

  // SubtleCrypto API를 사용하여 SHA-256 해시 생성
  const encoder = new TextEncoder();
  const data = encoder.encode(cert);
  
  return crypto.subtle.digest('SHA-256', data)
    .then(hashBuffer => {
      // ArrayBuffer를 16진수 문자열로 변환
      const hashArray = Array.from(new Uint8Array(hashBuffer));
      const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
      return hashHex;
    })
    .catch(error => {
      throw new Error(`인증서 해시 실패: ${error.message}`);
    });
}