package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Validar que los parámetros de entrada sean consistentes
	if count <= 0 || len(usernames) != count || len(passwords) != count {
		return nil
	}

	// Inicializar la slice de resultados
	results := make([][2]string, count)

	// Configuración de parámetros PBKDF2
	iterations := 10000
	keyLength := sha256.Size // 32 bytes para SHA-256

	for i := 0; i < count; i++ {
		// Generar una sal aleatoria de la misma longitud que el hash de salida
		salt := make([]byte, keyLength)
		_, err := rand.Read(salt)
		if err != nil {
			// En caso de error al generar la sal, continuar con el siguiente usuario
			continue
		}

		// Aplicar PBKDF2-HMAC-SHA256
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, keyLength, sha256.New)

		// Convertir a formato hexadecimal para almacenamiento
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Almacenar en el formato requerido: [hashedPassword, salt]
		results[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return results
}