import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	results := make([][2]string, count)
	
	for i := 0; i < count; i++ {
		// 32바이트(256비트) 솔트 생성 - SHA-256 출력 길이와 동일
		salt := make([]byte, 32)
		rand.Read(salt)
		
		// PBKDF2-HMAC-SHA256으로 비밀번호 해싱
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		
		// 16진수 문자열로 인코딩
		hashedHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)
		
		results[i] = [2]string{hashedHex, saltHex}
	}
	
	return results
}