package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey genera una chiave RSA privata, esportala utilizzando il formato PEM e restituiscila come stringa.
func CreatePrivateKey() string {
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Errore nella generazione della chiave:", err)
		return ""
	}

	privASN1 := privateKey.PrivateKey
	privPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: x509.MarshalPKCS1PrivateKey(privASN1),
	})

	return string(privPEM)
}