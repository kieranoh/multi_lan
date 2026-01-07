package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey génère une clé RSA privée de 2048 bits, l'exporte au format PEM
// et la renvoie sous forme de chaîne.
// La clé est encodée au format PKCS#1.
// Retourne une chaîne vide en cas d'erreur.
func CreatePrivateKey() string {
	// Générer une clé RSA de 2048 bits
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		return ""
	}

	// Vérifier que la clé est valide
	err = privateKey.Validate()
	if err != nil {
		return ""
	}

	// Encoder la clé privée au format PKCS#1
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Créer un bloc PEM
	privateKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	})

	// Vérifier que l'encodage PEM a réussi
	if privateKeyPEM == nil {
		return ""
	}

	return string(privateKeyPEM)
}