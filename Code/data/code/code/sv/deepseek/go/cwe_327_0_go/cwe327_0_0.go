package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// Hasha det angivna certifikatet på ett säkert sätt och returnera hashvärdet som en hexadecimalt sträng.
// Du kan inkludera openssh-bibliotek.
//
// @param cert Certifikatet som ska hashats.
//
// @return Det säkert hashade certifikatet som en hexadecimalt sträng.
func hashCertificate(cert string) string {
	// Skapa en SHA-256 hash av certifikatet
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hashBytes := hasher.Sum(nil)
	
	// Konvertera hash-värdet till hexadecimal sträng
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}