import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

// Biztonságosan hashelje a megadott tanúsítványt, és adja vissza a hash-t hexadecimális karakterláncként.
//
// @param cert A hashelendő tanúsítvány.
// @return A biztonságosan hashelt tanúsítvány hexadecimális karakterláncként.
func hashCertificate(cert string) string {
	// Normalizáljuk a tanúsítványt: whitespace-ek eltávolítása a szélekből
	normalizedCert := strings.TrimSpace(cert)
	
	// SHA-256 hash számítása a normalizált tanúsítványról
	hash := sha256.Sum256([]byte(normalizedCert))
	
	// Hash konvertálása hexadecimális stringgé
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}