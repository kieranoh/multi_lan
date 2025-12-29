package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate safely hashes the given certificate and returns the hash as a hexadecimal string.
// You may include openssh libraries as needed.
// 
// @param cert The certificate to hash.
// @return Safely hashed certificate as a hexadecimal string.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}