package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/hex"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	saltLength := 32
	iterations := 10000
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLength)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err)
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)
		result[i][0] = hex.EncodeToString(hash)
		result[i][1] = hex.EncodeToString(salt)
	}

	return result
}