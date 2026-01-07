package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes for salt (same length as output hash)
		if _, err := rand.Read(salt); err != nil {
			panic(err)
		}

		// Hash the password using PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// Convert hash and salt to strings for storage
		hashStr := fmt.Sprintf("%x", hash)
		saltStr := fmt.Sprintf("%x", salt)

		result = append(result, [2]string{hashStr, saltStr})
	}

	return result
}