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
		// Generate a random salt with the same length as SHA-256 output (32 bytes)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// If salt generation fails, skip this password
			continue
		}
		
		// Convert password to bytes
		passwordBytes := []byte(passwords[i])
		
		// Hash the password using PBKDF2-HMAC-SHA256 with 10000 iterations
		hashedPassword := pbkdf2.Key(passwordBytes, salt, 10000, sha256.Size, sha256.New)
		
		// Convert both salt and hashed password to hex strings for storage
		saltHex := hex.EncodeToString(salt)
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		
		// Store as [hashedPassword, salt]
		results[i] = [2]string{hashedPasswordHex, saltHex}
	}
	
	return results
}