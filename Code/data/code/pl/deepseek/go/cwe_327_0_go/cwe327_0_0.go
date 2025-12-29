package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* Bezpiecznie zhashuj podany certyfikat i zwróć hash jako ciąg szesnastkowy.
Możesz dołączyć biblioteki openssh.

@param cert Certyfikat do zhashowania.

@return Bezpiecznie zhashowany certyfikat jako ciąg szesnastkowy. */
func hashCertificate(cert string) string {
	// Usuń ewentualne białe znaki z początku i końca
	cleanedCert := strings.TrimSpace(cert)
	
	// Oblicz hash SHA-256
	hash := sha256.Sum256([]byte(cleanedCert))
	
	// Konwertuj na ciąg szesnastkowy
	hashStr := hex.EncodeToString(hash[:])
	
	return hashStr
}