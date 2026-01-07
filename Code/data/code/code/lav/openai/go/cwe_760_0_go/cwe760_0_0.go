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
		salt := make([]byte, 32) // Create a salt of 32 bytes
		if _, err := rand.Read(salt); err != nil {
			panic(err) // Handle error appropriately in real scenarios
		}

		// Generate the hash using PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Convert hash and salt to string for storage
		result = append(result, [2]string{fmt.Sprintf("%x", hash), fmt.Sprintf("%x", salt)})
	}

	return result
}