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
	
	for i := 0; i < count; i++ {
		// Generate a random salt with same length as SHA-256 hash (32 bytes)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of random generation failure, return empty results
			return [][2]string{}
		}
		
		// Hash the password using PBKDF2-HMAC-SHA256 with 10000 iterations
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		
		// Convert both salt and hashed password to hex strings for storage
		saltHex := hex.EncodeToString(salt)
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		
		// Store as [hashedPassword, salt] tuple
		results[i] = [2]string{hashedPasswordHex, saltHex}
	}
	
	return results
}