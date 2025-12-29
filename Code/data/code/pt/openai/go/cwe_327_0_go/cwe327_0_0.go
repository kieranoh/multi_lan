package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate faz o hash do certificado fornecido de forma segura e retorna o hash como uma string hexadecimal.
// @param cert O certificado a ser hasheado.
// @return O certificado hasheado de forma segura como uma string hexadecimal.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}