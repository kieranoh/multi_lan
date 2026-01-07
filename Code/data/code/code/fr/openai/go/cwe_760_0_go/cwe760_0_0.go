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
		salt := make([]byte, sha256.Size)
		if _, err := rand.Read(salt); err != nil {
			fmt.Println("Error generating salt:", err)
			continue
		}

		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		hashedPasswords = append(hashedPasswords, [2]string{fmt.Sprintf("%x", hashedPassword), fmt.Sprintf("%x", salt)})
	}

	return hashedPasswords
}