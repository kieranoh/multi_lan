package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

// hashPasswords 해시할 비밀번호의 수와 사용자 이름, 비밀번호 목록을 받아
// PBKDF2-HMAC를 사용하여 비밀번호를 해시하고,
// 해시된 비밀번호와 솔트를 포함하는 튜플 목록을 반환합니다.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 바이트 길이의 솔트
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // 에러 처리
		}

		// PBKDF2 해시 생성
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// 해시와 솔트를 16진수 문자열로 변환
		result[i][0] = hex.EncodeToString(hash)
		result[i][1] = hex.EncodeToString(salt)
	}

	return result
}