package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate Biztonságosan hashelje a megadott tanúsítványt, és adja vissza a hash-t hexadecimális karakterláncként.
//
// @param cert A hashelendő tanúsítvány.
// @return A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként.
func hashCertificate(cert string) string {
	hash := sha256.Sum256([]byte(cert))
	return hex.EncodeToString(hash[:])
}