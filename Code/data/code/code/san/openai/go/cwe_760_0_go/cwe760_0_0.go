package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

const (
	saltLength = 32
	iterations = 10000
)

// hashPasswords hashes user passwords using PBKDF2-HMAC with SHA-256.
// It returns a slice of tuples containing the hashed passwords and the salts used.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLength)
		if _, err := rand.Read(salt); err != nil {
			panic("failed to generate salt")
		}

		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)
		result[i] = [2]string{
			fmt.Sprintf("%x", hashedPassword), // convert to hex string
			fmt.Sprintf("%x", salt),            // convert salt to hex string
		}
	}

	return result
}