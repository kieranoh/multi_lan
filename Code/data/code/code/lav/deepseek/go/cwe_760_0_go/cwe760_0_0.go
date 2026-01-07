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

	for i := 0; i < count; i++ {
		// Generate a random salt of 32 bytes (same length as SHA-256 output)
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of random generation failure, return empty results
			return [][2]string{}
		}

		// Derive key using PBKDF2-HMAC-SHA256 with 10000 iterations
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// Convert both salt and hash to hex strings for storage
		saltHex := hex.EncodeToString(salt)
		hashHex := hex.EncodeToString(hash)

		// Store as [hash, salt] tuple
		results[i] = [2]string{hashHex, saltHex}
	}

	return results
}