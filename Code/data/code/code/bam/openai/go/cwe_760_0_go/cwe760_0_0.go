package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes salt
		if _, err := rand.Read(salt); err != nil {
			panic(err) // In production, handle error properly
		}
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		result[i][0] = hex.EncodeToString(hashedPassword)
		result[i][1] = hex.EncodeToString(salt)
	}

	return result
}