package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate Hashea el certificado dado de forma segura y devuelve el hash como una cadena hexadecimal.
// @param cert El certificado que se va a hashear.
// @return El certificado hasheado de forma segura como una cadena hexadecimal.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	return hex.EncodeToString(hasher.Sum(nil))
}