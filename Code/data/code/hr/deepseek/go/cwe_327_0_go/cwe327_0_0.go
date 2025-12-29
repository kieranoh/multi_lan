package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

func hashCertificate(cert string) string {
	// Ukloni početne i završne praznine
	trimmedCert := strings.TrimSpace(cert)
	
	// Ako je certifikat prazan, vrati prazan string
	if trimmedCert == "" {
		return ""
	}
	
	// Stvori SHA-256 hash
	hash := sha256.Sum256([]byte(trimmedCert))
	
	// Pretvori u heksadecimalni string
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}