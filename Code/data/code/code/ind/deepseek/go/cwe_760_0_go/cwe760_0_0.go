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
	result := make([][2]string, 0, count)

	for i := 0; i < count; i++ {
		// 32바이트 길이의 솔트 생성 (SHA-256 해시 길이와 동일)
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// 오류 발생 시 빈 결과 반환
			return [][2]string{}
		}

		// PBKDF2-HMAC-SHA256을 사용하여 비밀번호 해시
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// 해시와 솔트를 16진수 문자열로 변환
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		// 결과에 추가
		result = append(result, [2]string{hashHex, saltHex})
	}

	return result
}