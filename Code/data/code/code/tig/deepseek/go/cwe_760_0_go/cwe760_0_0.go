package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	results := make([][2]string, count)
	
	for i := 0; i < count; i++ {
		// Generate random salt with same length as output hash (SHA-256 = 32 bytes)
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of error, we'll use a fallback approach
			// This shouldn't happen in practice
			panic(fmt.Sprintf("Failed to generate salt: %v", err))
		}
		
		// Hash password using PBKDF2-HMAC-SHA256 with 10000 iterations
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		
		// Convert to hex strings for storage
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)
		
		// Store as [hash, salt] tuple
		results[i] = [2]string{hashHex, saltHex}
	}
	
	return results
}