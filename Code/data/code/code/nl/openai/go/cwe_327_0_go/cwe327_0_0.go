package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate hacht het gegeven certificaat veilig en retourneert de hash als een hexadecimale string.
// @param cert Het certificaat dat gehasht moet worden.
// @return Het veilig gehashte certificaat als een hexadecimale string.
func hashCertificate(cert string) string {
	hasher := sha256.New()
	hasher.Write([]byte(cert))
	hash := hasher.Sum(nil)
	return hex.EncodeToString(hash)
}