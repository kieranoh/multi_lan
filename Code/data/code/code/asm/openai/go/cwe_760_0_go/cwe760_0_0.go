package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes for salt
		_, err := rand.Read(salt)
		if err != nil {
			panic(err)
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
		hashString := base64.StdEncoding.EncodeToString(hash)
		saltString := base64.StdEncoding.EncodeToString(salt)

		result[i] = [2]string{hashString, saltString}
	}

	return result
}