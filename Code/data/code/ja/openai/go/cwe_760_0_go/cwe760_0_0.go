package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

// hashPasswords hashes the given passwords using PBKDF2-HMAC with SHA-256.
// It returns a slice of tuples containing the hashed password and the salt used for hashing.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes for salt
		if _, err := rand.Read(salt); err != nil {
			panic("failed to generate salt: " + err.Error())
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashedPassword := base64.StdEncoding.EncodeToString(hash)
		saltBase64 := base64.StdEncoding.EncodeToString(salt)

		results[i] = [2]string{hashedPassword, saltBase64}
	}

	return results
}

func main() {
	// Sample main function for testing.
}