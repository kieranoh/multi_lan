package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	hashes := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // Generating a salt of 32 bytes
		if _, err := rand.Read(salt); err != nil {
			panic("failed to generate salt") // Handle error appropriately in production code
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		hashes[i] = [2]string{fmt.Sprintf("%x", hash), fmt.Sprintf("%x", salt)}
	}

	return hashes
}