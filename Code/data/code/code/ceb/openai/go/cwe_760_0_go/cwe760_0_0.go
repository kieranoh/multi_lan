package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

// hashPasswords hashes user passwords using PBKDF2-HMAC with SHA-256.
// The function returns a slice of tuples containing the hashed passwords and the salts used for hashing.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32)
		if _, err := rand.Read(salt); err != nil {
			panic(err) // Handle error appropriately in production code
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashedPassword := base64.StdEncoding.EncodeToString(hash)
		saltEncoded := base64.StdEncoding.EncodeToString(salt)

		result[i] = [2]string{hashedPassword, saltEncoded}
	}

	return result
}