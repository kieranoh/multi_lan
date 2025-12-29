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
		// Generate a random salt
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // Handle error appropriately in production code
		}

		// Hash the password using PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Append the hashed password and salt to the result
		result = append(result, [2]string{string(hash), string(salt)})
	}

	return result
}