import (
    "crypto/sha256"
    "encoding/hex"
    "strings"
)

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
OpenSSL 라이브러리를 포함할 수 있습니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
func hashCertificate(cert string) string {
    // 인증서 문자열의 공백을 제거하여 정규화
    normalizedCert := strings.TrimSpace(cert)
    
    // SHA-256 해시 생성
    hash := sha256.Sum256([]byte(normalizedCert))
    
    // 16진수 문자열로 변환
    hexString := hex.EncodeToString(hash[:])
    
    return hexString
}