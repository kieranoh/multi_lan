package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate securely hashes the given certificate using SHA-256
// and returns the hash as a hexadecimal string.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}