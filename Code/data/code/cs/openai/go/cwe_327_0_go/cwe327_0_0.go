package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate bezpečně zhashtujte daný certifikát a vraťte hash jako hexadecimální řetězec.
// @param cert Certifikát, který má být zhashtován.
// @return Bezpečně zhashtovaný certifikát jako hexadecimální řetězec.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}