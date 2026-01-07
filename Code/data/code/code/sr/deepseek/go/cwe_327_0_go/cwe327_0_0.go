import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

func hashCertificate(cert string) string {
	// Ukloni početne i završne razmake
	trimmedCert := strings.TrimSpace(cert)
	
	// Proveri da li je sertifikat prazan
	if trimmedCert == "" {
		return ""
	}
	
	// Kreiraj SHA-256 hash
	hash := sha256.Sum256([]byte(trimmedCert))
	
	// Konvertuj u heksadecimalni string
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}