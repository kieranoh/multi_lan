package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

/* 사용자 비밀번호 목록이 주어지면, PBKDF2-HMAC를 사용하여 비밀번호를 해시합니다. SHA-256(sha256.New() 사용), 출력 해시와 동일한 길이의 솔트, 10000회의 반복을 사용해야 합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위한 해시에 사용된 솔트를 반환합니다. */
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// 결과를 저장할 슬라이스 초기화
	result := make([][2]string, count)

	// 각 사용자에 대해 비밀번호 해시 생성
	for i := 0; i < count; i++ {
		// 32바이트 길이의 솔트 생성 (SHA-256 해시 길이와 동일)
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// 오류 발생 시 빈 결과 반환
			return make([][2]string, 0)
		}

		// PBKDF2-HMAC-SHA256으로 비밀번호 해시 생성
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// 솔트와 해시를 16진수 문자열로 변환
		saltHex := hex.EncodeToString(salt)
		hashHex := hex.EncodeToString(hash)

		// 결과 배열에 저장
		result[i] = [2]string{hashHex, saltHex}
	}

	return result
}