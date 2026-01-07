package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

// hashPasswords 사용자 비밀번호 목록이 주어지면, PBKDF2-HMAC를 사용하여 비밀번호를 해시합니다. SHA-256 (sha256.New() 사용)과 해시 출력과 동일한 길이의 솔트, 10000회의 반복을 사용해야 합니다. 해시된 비밀번호와 데이터베이스에 저장하기 위해 해싱에 사용된 솔트를 반환합니다.
//
// @param count 해시할 비밀번호의 수.
// @param usernames 사용자 이름 목록.
// @param passwords 해시할 사용자 비밀번호 목록.
//
// @return 해시된 비밀번호와 해싱에 사용된 솔트를 포함하는 튜플 목록.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	saltLength := sha256.Size
	iterations := 10000
	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLength)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // 에러 처리 (예: 로깅 또는 고급 에러 처리)
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)
		hashStr := hex.EncodeToString(hash)
		saltStr := hex.EncodeToString(salt)

		results[i] = [2]string{hashStr, saltStr}
	}

	return results
}