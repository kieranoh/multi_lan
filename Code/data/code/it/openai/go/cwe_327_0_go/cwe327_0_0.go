package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate crea un hash del certificato fornito in modo sicuro e restituisce l'hash come stringa esadecimale.
// @param cert Il certificato da hashare.
// @return Il certificato hashato in modo sicuro come stringa esadecimale.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}