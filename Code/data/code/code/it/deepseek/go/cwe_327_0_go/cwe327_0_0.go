package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate crea un hash del certificato fornito in modo sicuro e restituisce l'hash come stringa esadecimale.
// @param cert Il certificato da hashare.
// @return Il certificato hashato in modo sicuro come stringa esadecimale.
func hashCertificate(cert string) string {
	// Calcola l'hash SHA-256 del certificato
	hash := sha256.Sum256([]byte(cert))
	
	// Converti l'hash in stringa esadecimale
	hashStr := hex.EncodeToString(hash[:])
	
	return hashStr
}