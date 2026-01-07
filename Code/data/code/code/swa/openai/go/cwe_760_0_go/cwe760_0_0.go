package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 256 bits for salt
		if _, err := rand.Read(salt); err != nil {
			continue // Error handling can be improved
		}

		// Generate the hashed password using PBKDF2 with HMAC-SHA256
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Encode the hashed password and salt to base64 for storage
		hashedPasswordBase64 := base64.StdEncoding.EncodeToString(hashedPassword)
		saltBase64 := base64.StdEncoding.EncodeToString(salt)

		// Append the result
		result = append(result, [2]string{hashedPasswordBase64, saltBase64})
	}

	return result
}