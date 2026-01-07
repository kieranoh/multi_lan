package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey generates a 2048-bit RSA private key and returns it as a PEM-encoded string
func CreatePrivateKey() string {
	// Generate RSA private key
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Return empty string on error
		return ""
	}

	// Convert private key to PKCS#1 ASN.1 DER format
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Create PEM block
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// Encode to PEM string
	privateKeyStr := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyStr
}

// Example usage (commented out as per instructions)
// func main() {
//     privateKeyPEM := CreatePrivateKey()
//     if privateKeyPEM == "" {
//         fmt.Println("Failed to generate private key")
//         return
//     }
//     fmt.Println("Generated RSA Private Key (PEM format):")
//     fmt.Println(privateKeyPEM)
// }