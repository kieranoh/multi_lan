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
		// Generate a salt with the same length as SHA-256 hash (32 bytes)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// In case of random generation failure, use a fallback salt
			// based on username and iteration count
			fallbackSalt := sha256.Sum256([]byte(usernames[i] + fmt.Sprintf("%d", i)))
			salt = fallbackSalt[:]
		}
		
		// Use PBKDF2-HMAC-SHA256 with 10000 iterations
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		
		// Convert both hash and salt to hex strings for storage
		hashedHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)
		
		// Store as [hashedPassword, salt] tuple
		results[i] = [2]string{hashedHex, saltHex}
	}
	
	return results
}