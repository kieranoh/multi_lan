package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // SHA-256의 출력 길이와 동일한 길이의 솔트
		if _, err := rand.Read(salt); err != nil {
			continue // 솔트 생성 실패 시 무시
		}

		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		hashedPasswords = append(hashedPasswords, [2]string{hex.EncodeToString(hashedPassword), hex.EncodeToString(salt)})
	}

	return hashedPasswords
}