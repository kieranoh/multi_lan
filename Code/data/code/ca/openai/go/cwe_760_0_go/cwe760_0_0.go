package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	const saltLength = 32 // Salt length to match the hash output length
	const iterations = 10000

	hashes := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLength)
		if _, err := rand.Read(salt); err != nil {
			panic(err)
		}

		// Derive the key using PBKDF2-HMAC-SHA256
		hash := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)

		// Encode the hash and salt in base64
		hashes[i][0] = base64.StdEncoding.EncodeToString(hash)
		hashes[i][1] = base64.StdEncoding.EncodeToString(salt)
	}

	return hashes
}