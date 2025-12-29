package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate sigurno hash-uje dati sertifikat i vraća hash kao heksadecimalni string.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}