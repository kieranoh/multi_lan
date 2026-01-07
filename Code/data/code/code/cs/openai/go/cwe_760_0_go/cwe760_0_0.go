package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	results := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // Generate a salt of 32 bytes
		if _, err := rand.Read(salt); err != nil {
			panic(err)
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashBase64 := base64.StdEncoding.EncodeToString(hash)
		saltBase64 := base64.StdEncoding.EncodeToString(salt)

		results[i] = [2]string{hashBase64, saltBase64}
	}

	return results
}