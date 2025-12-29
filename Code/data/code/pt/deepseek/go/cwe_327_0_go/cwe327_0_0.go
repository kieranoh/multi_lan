package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

/* Faça o hash do certificado fornecido de forma segura e retorne o hash como uma string hexadecimal.
Você pode incluir bibliotecas openssh.

@param cert O certificado a ser hasheado.

@return O certificado hasheado de forma segura como uma string hexadecimal. */
func hashCertificate(cert string) string {
	// Cria um novo hash SHA-256
	hasher := sha256.New()
	
	// Escreve o certificado no hasher
	hasher.Write([]byte(cert))
	
	// Obtém o hash como slice de bytes
	hashBytes := hasher.Sum(nil)
	
	// Converte para string hexadecimal
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}