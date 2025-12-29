package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

func hashCertificate(cert string) string {
	// Crear un hash SHA-256 del certificat
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hashBytes := hasher.Sum(nil)
	
	// Convertir el hash a cadena hexadecimal
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}