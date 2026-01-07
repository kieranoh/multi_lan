package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate securely hashes the provided certificate and returns the hash as a hexadecimal string.
//
// @param cert The certificate to hash.
//
// @return A securely hashed certificate in hexadecimal string format.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	return hex.EncodeToString(hasher.Sum(nil))
}