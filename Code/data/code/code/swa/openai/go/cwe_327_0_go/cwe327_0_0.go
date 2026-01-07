package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate securely hashes the given certificate and returns the hash as a hexadecimal string.
// It includes the OpenSSH library.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}