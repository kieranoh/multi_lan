package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 256 bits for SHA-256
		if _, err := rand.Read(salt); err != nil {
			panic(err) // handle error appropriately in real scenarios
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		result = append(result, [2]string{hashHex, saltHex})
	}

	return result
}