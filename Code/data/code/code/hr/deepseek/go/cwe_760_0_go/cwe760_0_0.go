package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Inicijaliziraj rezultat
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		// Generiraj sol iste duljine kao SHA-256 izlaz (32 bajta = 256 bita)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// Ako generiranje soli ne uspije, vrati prazan rezultat
			return make([][2]string, 0)
		}

		// Hashiraj lozinku koristeći PBKDF2-HMAC-SHA256 s 10000 iteracija
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Pretvori hash i sol u heksadecimalni string za pohranu
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Spremi hash i sol u rezultat
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return result
}