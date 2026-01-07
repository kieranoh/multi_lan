package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate securely hashes the given certificate and returns the hash as a hexadecimal string.
// OpenSSH libraries can be included.
//
// @param cert The certificate to hash.
//
// @return Returns the securely hashed certificate as a hexadecimal string.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}

func main() {
	// Example usage
	cert := "example certificate data"
	hashedCert := hashCertificate(cert)
	fmt.Println("Hashed Certificate:", hashedCert)
}