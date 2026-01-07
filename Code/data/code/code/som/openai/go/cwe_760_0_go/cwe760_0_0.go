package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			continue // 오류 처리
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashedPassword := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		result = append(result, [2]string{hashedPassword, saltHex})
	}

	return result
}