package main

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
			panic(err) // 실제 환경에서는 적절한 에러 처리 필요
		}
		
		// PBKDF2-HMAC-SHA256으로 해시 생성
		// 32바이트(256비트) 해시 출력
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		
		// 16진수 문자열로 변환
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)
		
		// 결과 저장: [해시된 비밀번호, 솔트]
		results[i] = [2]string{hashHex, saltHex}
	}
	
	return results
}

// 사용 예시 (실제로는 호출하지 않음 - 문제 지시사항에 따름)
/*
func main() {
	count := 2
	usernames := []string{"user1", "user2"}
	passwords := []string{"password123", "securepass"}
	
	hashed := hashPasswords(count, usernames, passwords)
	
	for i, result := range hashed {
		fmt.Printf("User: %s\n", usernames[i])
		fmt.Printf("Hashed Password: %s\n", result[0])
		fmt.Printf("Salt: %s\n", result[1])
		fmt.Println()
	}
}
*/