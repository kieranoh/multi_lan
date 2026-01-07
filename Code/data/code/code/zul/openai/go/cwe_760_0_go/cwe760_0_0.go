package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // Generating a salt of 32 bytes
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // Handle error appropriately in production code
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashedPassword := fmt.Sprintf("%x", hash)
		saltHex := fmt.Sprintf("%x", salt)

		hashedPasswords = append(hashedPasswords, [2]string{hashedPassword, saltHex})
	}

	return hashedPasswords
}