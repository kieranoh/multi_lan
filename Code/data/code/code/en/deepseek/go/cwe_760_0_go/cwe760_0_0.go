package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
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
		// Generate random salt of same length as hash output
		salt := make([]byte, hashSize)
		_, err := rand.Read(salt)
		if err != nil {
			// If salt generation fails, return empty results
			return [][2]string{}
		}

		// Hash password using PBKDF2-HMAC-SHA256
		hashed := pbkdf2.Key([]byte(passwords[i]), salt, 10000, hashSize, sha256.New)

		// Convert to hex strings for storage
		hashedHex := hex.EncodeToString(hashed)
		saltHex := hex.EncodeToString(salt)

		results[i] = [2]string{hashedHex, saltHex}
	}

	return results
}