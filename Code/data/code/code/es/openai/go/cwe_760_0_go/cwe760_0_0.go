package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, 32) // SHA-256 salida es de 32 bytes
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // Manejo de errores simple
		}

		// Hashear la contraseña
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// Codificar el hash y la sal en base64 para almacenamiento
		hashedPassword := base64.StdEncoding.EncodeToString(hash)
		saltEncoded := base64.StdEncoding.EncodeToString(salt)

		// Agregar resultado a la lista
		hashedPasswords = append(hashedPasswords, [2]string{hashedPassword, saltEncoded})
	}

	return hashedPasswords
}