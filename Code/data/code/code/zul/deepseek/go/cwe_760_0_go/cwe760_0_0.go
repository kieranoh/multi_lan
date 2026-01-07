import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	results := make([][2]string, count)
	
	for i := 0; i < count; i++ {
		// 32바이트(256비트) 솔트 생성
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			panic(fmt.Sprintf("솔트 생성 실패: %v", err))
		}
		
		// PBKDF2-HMAC-SHA256으로 해시 생성 (10000회 반복)
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		
		// 16진수 문자열로 변환
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)
		
		// 결과 저장: [해시된 비밀번호, 솔트]
		results[i] = [2]string{hashHex, saltHex}
	}
	
	return results
}