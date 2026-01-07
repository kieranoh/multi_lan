package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	hashes := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 bytes salt
		if _, err := rand.Read(salt); err != nil {
			panic(err)
		}

		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New) // 32 bytes output length
		hashes[i][0] = base64.StdEncoding.EncodeToString(hashedPassword)
		hashes[i][1] = base64.StdEncoding.EncodeToString(salt)
	}

	return hashes
}