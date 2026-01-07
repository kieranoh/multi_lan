package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // Length of the salt should match the hash output length
		if _, err := rand.Read(salt); err != nil {
			return nil // Handle error gracefully
		}

		// PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Store hashed password and salt in hex
		hashedPasswords = append(hashedPasswords, [2]string{hex.EncodeToString(hash), hex.EncodeToString(salt)})
	}

	return hashedPasswords
}