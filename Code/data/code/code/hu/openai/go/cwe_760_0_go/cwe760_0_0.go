package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 256 bit salt
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // Handle error appropriately in production code
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		hashedPassword := base64.StdEncoding.EncodeToString(hash)
		saltEncoded := base64.StdEncoding.EncodeToString(salt)

		hashedPasswords = append(hashedPasswords, [2]string{hashedPassword, saltEncoded})
	}

	return hashedPasswords
}