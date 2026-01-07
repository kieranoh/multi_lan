package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate hashes the given certificate securely and returns the hash as a hexadecimal string.
// @param cert The certificate to hash.
// @return The securely hashed certificate as a hexadecimal string.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}