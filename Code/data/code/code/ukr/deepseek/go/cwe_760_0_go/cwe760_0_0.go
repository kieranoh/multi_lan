import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)
	
	for i := 0; i < count; i++ {
		// 32바이트 솔트 생성 (SHA-256 출력 길이와 동일)
		salt := make([]byte, 32)
		rand.Read(salt)
		
		// PBKDF2-HMAC-SHA256으로 비밀번호 해싱
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		
		// 16진수 문자열로 변환
		hashedHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)
		
		// 결과 저장: [해시된 비밀번호, 솔트]
		result[i] = [2]string{hashedHex, saltHex}
	}
	
	return result
}