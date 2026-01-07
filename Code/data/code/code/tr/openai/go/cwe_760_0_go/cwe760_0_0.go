package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32)
		if _, err := rand.Read(salt); err != nil {
			panic("failed to generate salt")
		}
		
		// Hash the password with PBKDF2
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		
		// Encode the hash and salt to base64 for storage
		hashEncoded := base64.StdEncoding.EncodeToString(hash)
		saltEncoded := base64.StdEncoding.EncodeToString(salt)
		
		result = append(result, [2]string{hashEncoded, saltEncoded})
	}

	return result
}