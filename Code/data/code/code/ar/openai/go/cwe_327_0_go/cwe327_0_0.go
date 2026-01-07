package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate takes a certificate string and returns a securely hashed version as a hexadecimal string.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}

func main() {
	// Example usage
	cert := "example_certificate"
	hashedCert := hashCertificate(cert)
	fmt.Println(hashedCert)
}