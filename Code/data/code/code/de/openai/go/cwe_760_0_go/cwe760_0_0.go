package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

// hashPasswords hasht die Passwörter der Benutzer mit PBKDF2-HMAC unter Verwendung von SHA-256.
// Es generiert auch zufällige Salze für jedes Passwort und gibt die gehashten Passwörter sowie die verwendeten Salze zurück.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	if count <= 0 || len(usernames) != count || len(passwords) != count {
		return nil
	}

	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // 32 Bytes für SHA-256
		if _, err := rand.Read(salt); err != nil {
			continue // Fehler beim Erzeugen des Salzes
		}

		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		result[i] = [2]string{
			base64.StdEncoding.EncodeToString(hashedPassword),
			base64.StdEncoding.EncodeToString(salt),
		}
	}

	return result
}