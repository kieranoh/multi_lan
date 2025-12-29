package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

// hashPasswords hashes user passwords using PBKDF2-HMAC with SHA-256.
// It takes the number of passwords to hash, a slice of usernames,
// and a slice of passwords as input parameters.
// It returns a slice of tuples containing the hashed passwords and the salts used for hashing.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)
	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // Salt of length 32 bytes (256 bits)
		if _, err := rand.Read(salt); err != nil {
			panic(err) // Handle error appropriately in production code
		}

		// Hash the password using PBKDF2 with SHA-256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Store the base64 encoded hashed password and salt
		result[i][0] = base64.StdEncoding.EncodeToString(hash)
		result[i][1] = base64.StdEncoding.EncodeToString(salt)
	}
	return result
}