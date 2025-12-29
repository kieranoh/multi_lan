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
	if len(usernames) < count || len(passwords) < count {
		// Return empty result if inputs don't match expected count
		return make([][2]string, 0)
	}

	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		// Generate salt with same length as SHA-256 output (32 bytes)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// If salt generation fails, use a fallback with username and random data
			fallbackSalt := sha256.Sum256([]byte(usernames[i] + string(salt)))
			salt = fallbackSalt[:]
		}

		// Use PBKDF2-HMAC-SHA256 with 10000 iterations
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Convert both to hex strings for storage
		hashedHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Store as tuple [hashedPassword, salt]
		results[i] = [2]string{hashedHex, saltHex}
	}

	return results
}