package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate Segurtasunez hashatu eta hash-a hexadizimal kate gisa itzuli.
// @param cert Hashatu beharreko ziurtagiria.
// @return Segurtasunez hashatutako ziurtagiria hexadizimal kate gisa.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}