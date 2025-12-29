package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate hashaa annettu sertifikaatti turvallisesti ja palauta hash heksadesimaalimuotoisena merkkijonona.
// @param cert Hashattava sertifikaatti.
// @return Turvallisesti hashattu sertifikaatti heksadesimaalimuotoisena merkkijonona.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}