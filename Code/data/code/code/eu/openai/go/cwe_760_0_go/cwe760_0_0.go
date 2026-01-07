package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

const saltLength = 32 // Salt length in bytes
const iterations = 10000 // Number of PBKDF2 iterations

/* Erabiltzaileen pasahitzen zerrenda bat emanda, PBKDF2-HMAC erabili pasahitzak hashatzeko. SHA-256 (sha256.New() bidez) erabili behar duzu, irteera hasharen luzera bereko saltsak, eta 10000 iterazio. Itzuli hashatutako pasahitzak eta hashingerako erabilitako saltsak datu-basean gorde ahal izateko. */
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLength)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err)
		}

		hash := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)
		result[i] = [2]string{base64.StdEncoding.EncodeToString(hash), base64.StdEncoding.EncodeToString(salt)}
	}

	return result
}