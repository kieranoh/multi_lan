package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 256 bits = 32 bytes
		if _, err := rand.Read(salt); err != nil {
			panic(err) // handle error appropriately in production code
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		results[i] = [2]string{hashHex, saltHex}
	}

	return results
}