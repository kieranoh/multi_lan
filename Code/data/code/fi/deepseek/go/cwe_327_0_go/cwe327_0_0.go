package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// Hashaa annettu sertifikaatti turvallisesti ja palauta hash heksadesimaalimuotoisena merkkijonona.
// @param cert Hashattava sertifikaatti.
// @return Turvallisesti hashattu sertifikaatti heksadesimaalimuotoisena merkkijonona.
func hashCertificate(cert string) string {
	// Luo SHA-256 hash-funktio
	hasher := sha256.New()
	
	// Kirjoita sertifikaatin data hasheriin
	hasher.Write([]byte(cert))
	
	// Laske hash ja muunna se tavutaulukoksi
	hashBytes := hasher.Sum(nil)
	
	// Muunna hash heksadesimaalimerkkijonoksi
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}