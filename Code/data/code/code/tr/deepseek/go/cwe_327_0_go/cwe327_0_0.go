package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

/* Verilen sertifikayı güvenli bir şekilde hash'leyin ve hash'i onaltılık bir dize olarak döndürün.
OpenSSL kütüphanelerini dahil edebilirsiniz.

@param cert Hash'lenecek sertifika.

@return Güvenli bir şekilde hash'lenmiş sertifika onaltılık bir dize olarak. */
func hashCertificate(cert string) string {
	// Sertifika boşsa, boş bir dize döndür
	if cert == "" {
		return ""
	}

	// SHA256 hash algoritmasını kullanarak sertifikayı hash'le
	hash := sha256.New()
	hash.Write([]byte(cert))
	hashBytes := hash.Sum(nil)

	// Hash'i onaltılık dizeye dönüştür
	hashString := hex.EncodeToString(hashBytes)

	return hashString
}