package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

const (
	saltLength    = 32
	iterations    = 10000
	hashLength    = 32
)

// hashPasswords hešira lozinke koristeći PBKDF2-HMAC sa SHA-256.
// Vraća listu tuplova koja sadrži heširane lozinke i soli korišćene za heširanje.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	hashedPasswords := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLength)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // U pravom kodu, obradite greške na odgovarajući način
		}

		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, hashLength, sha256.New)
		hashedPasswords[i][0] = fmt.Sprintf("%x", hashedPassword)
		hashedPasswords[i][1] = fmt.Sprintf("%x", salt)
	}

	return hashedPasswords
}