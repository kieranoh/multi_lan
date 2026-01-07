package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate Güvenli bir şekilde hash'lenmiş sertifikayı döndürür.
// Verilen sertifikayı güvenli bir şekilde hash'leyin ve hash'i onaltılık bir dize olarak döndürün.
// @param cert Hash'lenecek sertifika.
// @return Güvenli bir şekilde hash'lenmiş sertifika onaltılık bir dize olarak.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}