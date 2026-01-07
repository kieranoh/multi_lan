package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

const (
	saltSize    = 32 // Salt size in bytes
	iterationCount = 10000 // Number of iterations
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, saltSize)
		if _, err := rand.Read(salt); err != nil {
			panic("failed to generate salt: " + err.Error())
		}

		// Hash the password using PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, iterationCount, sha256.Size, sha256.New)

		// Store the hashed password and salt in the result
		result = append(result, [2]string{fmt.Sprintf("%x", hash), fmt.Sprintf("%x", salt)})
	}

	return result
}