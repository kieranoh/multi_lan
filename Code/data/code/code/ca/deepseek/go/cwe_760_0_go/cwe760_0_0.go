package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Crear una llista per emmagatzemar els resultats
	result := make([][2]string, count)
	
	// Iterar sobre totes les contrasenyes
	for i := 0; i < count; i++ {
		// Generar un salt aleatori de la mateixa longitud que el hash SHA-256 (32 bytes)
		salt := make([]byte, sha256.Size)
		_, err := rand.Read(salt)
		if err != nil {
			// En cas d'error en la generació del salt, retornar una llista buida
			return make([][2]string, 0)
		}
		
		// Aplicar PBKDF2-HMAC amb SHA-256, 10000 iteracions
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		
		// Convertir el hash i el salt a representació hexadecimal
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)
		
		// Emmagatzemar el hash i el salt com a tupla
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}
	
	return result
}