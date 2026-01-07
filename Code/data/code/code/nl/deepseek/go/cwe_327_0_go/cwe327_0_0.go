package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// Hash het gegeven certificaat veilig en retourneer de hash als een hexadecimale string.
// Je kunt openssh-bibliotheken opnemen.
//
// @param cert Het certificaat dat gehasht moet worden.
// @return Het veilig gehashte certificaat als een hexadecimale string.
func hashCertificate(cert string) string {
	// Maak een nieuwe SHA-256 hash instantie
	hasher := sha256.New()
	
	// Schrijf de certificaat bytes naar de hash
	hasher.Write([]byte(cert))
	
	// Bereken de hash en converteer naar hexadecimale string
	hashBytes := hasher.Sum(nil)
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}