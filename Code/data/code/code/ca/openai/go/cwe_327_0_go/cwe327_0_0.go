package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.
// @param cert El certificat que s'ha de hashear.
// @return El certificat hashejat de manera segura com una cadena hexadecimal.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}