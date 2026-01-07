package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Validate input lengths
	if count <= 0 || len(usernames) < count || len(passwords) < count {
		return [][2]string{}
	}

	results := make([][2]string, count)
	hashSize := sha256.Size // 32 bytes

	for i := 0; i < count; i++ {
		// Generate random salt of the same length as hash output
		salt := make([]byte, hashSize)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of error, return empty results
			return [][2]string{}
		}

		// Hash the password using PBKDF2-HMAC-SHA256 with 10000 iterations
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, hashSize, sha256.New)

		// Convert both salt and hashed password to hex strings for storage
		saltHex := hex.EncodeToString(salt)
		hashedPasswordHex := hex.EncodeToString(hashedPassword)

		// Store as tuple: [hashedPassword, salt]
		results[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return results
}