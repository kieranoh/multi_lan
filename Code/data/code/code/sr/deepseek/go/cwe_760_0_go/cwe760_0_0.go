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
		return make([][2]string, 0)
	}

	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		// Generate a random salt of the same length as the hash output (32 bytes for SHA-256)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of error, return empty results
			return make([][2]string, 0)
		}

		// Use PBKDF2-HMAC-SHA256 with 10000 iterations
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Convert both hash and salt to hex strings for storage
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		// Store as tuple [hash, salt]
		results[i] = [2]string{hashHex, saltHex}
	}

	return results
}