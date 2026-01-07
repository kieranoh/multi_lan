package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

// hashCertificate hashea de forma segura el certificado dado y devuelve el hash como una cadena hexadecimal.
// @param cert El certificado que se va a hashear.
// @return El certificado hasheado de forma segura como una cadena hexadecimal.
func hashCertificate(cert string) string {
	// Limpiar el certificado eliminando espacios en blanco al inicio y final
	cleanedCert := strings.TrimSpace(cert)
	
	// Verificar que el certificado no esté vacío después de limpiarlo
	if cleanedCert == "" {
		return ""
	}
	
	// Crear un hash SHA-256
	hash := sha256.New()
	
	// Escribir el certificado en el hash
	hash.Write([]byte(cleanedCert))
	
	// Calcular el hash final
	hashBytes := hash.Sum(nil)
	
	// Convertir el hash a una cadena hexadecimal
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}