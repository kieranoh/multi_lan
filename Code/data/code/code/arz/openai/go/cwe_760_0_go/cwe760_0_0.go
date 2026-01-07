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
		salt := make([]byte, 32) // Generate a random salt of 32 bytes
		if _, err := rand.Read(salt); err != nil {
			panic(err) // Handle error appropriately in production code
		}
		
		// PBKDF2 hashing
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Encode the hash and salt to base64 for storage
		hashedPassword := base64.StdEncoding.EncodeToString(hash)
		saltEncoded := base64.StdEncoding.EncodeToString(salt)

		result = append(result, [2]string{hashedPassword, saltEncoded})
	}

	return result
}