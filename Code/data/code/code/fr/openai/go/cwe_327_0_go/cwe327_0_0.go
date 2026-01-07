package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate hache le certificat donné de manière sécurisée et renvoie le hachage sous forme de chaîne hexadécimale.
// @param cert Le certificat à hacher.
// @return Le certificat haché de manière sécurisée sous forme de chaîne hexadécimale.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}