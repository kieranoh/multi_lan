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
		salt := make([]byte, 32) // Generating a salt of 32 bytes length
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // Handle error appropriately in production code
		}

		// Hash the password using PBKDF2 with HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// Convert the hash and salt to hexadecimal for storage
		hashedPassword := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		// Append the hashed password and salt to the results
		hashedPasswords = append(hashedPasswords, [2]string{hashedPassword, saltHex})
	}

	return hashedPasswords
}