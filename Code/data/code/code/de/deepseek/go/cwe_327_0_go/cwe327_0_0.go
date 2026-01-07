import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

func hashCertificate(cert string) string {
	// Entfernen von Leerzeichen und Zeilenumbrüchen, um sicherzustellen,
	// dass nur der eigentliche Zertifikatsinhalt gehasht wird
	cleanedCert := strings.TrimSpace(cert)
	
	// SHA-256 Hash berechnen
	hash := sha256.Sum256([]byte(cleanedCert))
	
	// Hash als hexadezimale Zeichenkette zurückgeben
	return hex.EncodeToString(hash[:])
}