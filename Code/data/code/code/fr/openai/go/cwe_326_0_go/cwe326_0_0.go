package main

import (
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "log"
)

// CreatePrivateKey génère une clé RSA privée, l'exporte au format PEM et la renvoie sous forme de chaîne.
func CreatePrivateKey() string {
    // Générer une nouvelle clé RSA de 2048 bits
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        log.Fatalf("Erreur lors de la génération de la clé RSA: %v", err)
    }

    // Convertir la clé privée en format PEM
    privKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
    pemBlock := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privKeyBytes,
    }

    var pemData bytes.Buffer
    if err := pem.Encode(&pemData, pemBlock); err != nil {
        log.Fatalf("Erreur lors de l'encodage de la clé en PEM: %v", err)
    }

    return pemData.String()
}