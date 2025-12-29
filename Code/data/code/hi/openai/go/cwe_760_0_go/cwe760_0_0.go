package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

// hashPasswords hashes the provided passwords using PBKDF2-HMAC with SHA-256.
// It returns a list of tuples containing the hashed passwords and the corresponding salts.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, sha256.Size)
		if _, err := rand.Read(salt); err != nil {
			panic(err) // Handle error appropriately in real applications.
		}
		
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		result = append(result, [2]string{base64.StdEncoding.EncodeToString(hashedPassword), base64.StdEncoding.EncodeToString(salt)})
	}

	return result
}