package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// 결과를 저장할 슬라이스 초기화
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		// 32바이트 길이의 솔트 생성 (SHA-256 해시 길이와 동일)
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// 오류 발생 시 빈 결과 반환
			return make([][2]string, 0)
		}

		// PBKDF2-HMAC-SHA256을 사용하여 비밀번호 해싱
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// 16진수 문자열로 변환
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// 결과 저장: [해시된 비밀번호, 솔트]
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return result
}