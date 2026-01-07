package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes for the salt
		if _, err := rand.Read(salt); err != nil {
			panic(err) // handle error appropriately in production code
		}

		// PBKDF2-HMAC with SHA-256
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Store the hashed password and salt in the result
		result[i][0] = hex.EncodeToString(hashedPassword)
		result[i][1] = hex.EncodeToString(salt)
	}

	return result
}