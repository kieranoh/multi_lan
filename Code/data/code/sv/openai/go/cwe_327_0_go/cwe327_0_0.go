package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate hashes the given certificate securely and returns the hash value as a hexadecimal string.
//
// @param cert The certificate to be hashed.
// @return The securely hashed certificate as a hexadecimal string.
func hashCertificate(cert string) string {
	h := sha256.New()
	h.Write([]byte(cert))
	return hex.EncodeToString(h.Sum(nil))
}