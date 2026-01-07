package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // Generate a salt of the same length
		if _, err := rand.Read(salt); err != nil {
			panic(err) // Handle error appropriately in real scenarios
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		result[i] = [2]string{fmt.Sprintf("%x", hash), fmt.Sprintf("%x", salt)}
	}

	return result
}