package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate sigurno hashira dani certifikat i vraća hash kao heksadecimalni niz.
// @param cert Certifikat koji treba hashirati.
// @return Sigurno hashirani certifikat kao heksadecimalni niz.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}