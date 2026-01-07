package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

// hashPasswords hashes passwords using PBKDF2-HMAC-SHA256 with a salt of the same length as the output hash and 10000 iterations.
// It returns a list of tuples containing the hashed passwords and the salts used for hashing.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Validate input lengths
	if count <= 0 || len(usernames) != count || len(passwords) != count {
		return nil
	}

	// Initialize the result slice
	result := make([][2]string, count)

	// Hash each password
	for i := 0; i < count; i++ {
		// Generate a random salt of the same length as the SHA-256 hash (32 bytes)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of error, return nil
			return nil
		}

		// Hash the password using PBKDF2-HMAC-SHA256 with 10000 iterations
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Convert the hashed password and salt to hex strings for storage
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Store the hashed password and salt as a tuple
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return result
}