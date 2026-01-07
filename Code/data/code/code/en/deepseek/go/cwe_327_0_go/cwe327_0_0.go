package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

/*
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
func hashCertificate(cert string) string {
	// Create a new SHA-256 hash object
	hasher := sha256.New()
	
	// Write the certificate bytes to the hasher
	hasher.Write([]byte(cert))
	
	// Get the hash sum
	hashBytes := hasher.Sum(nil)
	
	// Convert the hash to a hexadecimal string
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}