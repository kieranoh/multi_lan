package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

// hashPasswords accepts a count of passwords to hash, a list of usernames, and a list of passwords.
// It returns a slice of tuples containing the hashed passwords and the salts used for hashing.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Create a slice to hold the results
	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		// Generate a random salt of the same length as the hash (32 bytes for SHA-256)
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err)
		}

		// Hash the password using PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// Convert the hash and the salt to string format (Base64 or hex)
		hashStr := fmt.Sprintf("%x", hash)
		saltStr := fmt.Sprintf("%x", salt)

		// Store the result in the slice
		results[i] = [2]string{hashStr, saltStr}
	}

	return results
}