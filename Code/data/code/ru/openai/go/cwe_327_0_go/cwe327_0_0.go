package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate надежно хеширует данный сертификат и возвращает хеш в виде шестнадцатичной строки.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}

func main() {
	// Пример использования функции (не для исполнения)
	cert := "example_certificate"
	hashedCert := hashCertificate(cert)
	fmt.Println(hashedCert)
}