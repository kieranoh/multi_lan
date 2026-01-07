package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
	"fmt"
)

// hashPasswords hashes user passwords using PBKDF2 with HMAC-SHA256.
// It returns a list of tuples containing the hashed passwords and salts used for hashing.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var result [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes salt
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // handle error appropriately in real scenarios
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashedPassword := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)

		result = append(result, [2]string{hashedPassword, saltHex})
	}

	return result
}