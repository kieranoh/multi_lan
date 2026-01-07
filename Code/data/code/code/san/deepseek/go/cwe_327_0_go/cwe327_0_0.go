/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
    // SHA-256 해시 생성
    hash := sha256.Sum256([]byte(cert))
    
    // 16진수 문자열로 변환
    hexString := hex.EncodeToString(hash[:])
    
    return hexString
}