import (
	"crypto/md5"
	"crypto/sha1"
	"crypto/sha256"
	"crypto/sha512"
	"encoding/hex"
	"fmt"
	"strings"
)

func hashCertificate(cert string) string {
	// Ziurtagiriaren formatua egiaztatu
	cert = strings.TrimSpace(cert)
	if cert == "" {
		return ""
	}

	// Ziurtagiriaren hasiera egiaztatu
	if !strings.HasPrefix(cert, "-----BEGIN") {
		return ""
	}

	// Ziurtagiriaren edukia atera (goiburu eta oineko lerroak kenduta)
	lines := strings.Split(cert, "\n")
	var certBody strings.Builder
	inBody := false

	for _, line := range lines {
		line = strings.TrimSpace(line)
		if strings.HasPrefix(line, "-----BEGIN") {
			inBody = true
			continue
		}
		if strings.HasPrefix(line, "-----END") {
			break
		}
		if inBody && line != "" {
			certBody.WriteString(line)
		}
	}

	certContent := certBody.String()
	if certContent == "" {
		return ""
	}

	// SHA256 hash-a kalkulatu ziurtagiriaren edukiarentzat
	hash := sha256.Sum256([]byte(certContent))
	
	// Hexadizimal formatura bihurtu
	hashStr := hex.EncodeToString(hash[:])
	
	return hashStr
}