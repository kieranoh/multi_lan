package main

import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "errors"
)

// Sortu RSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.
func CreatePrivateKey() string {
    // RSA gako pribatua sortu 2048 biteko luzerarekin
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        panic(errors.New("Ezin izan da RSA gako pribatua sortu: " + err.Error()))
    }

    // Egiaztatu gakoa baliozkoa dela
    err = privateKey.Validate()
    if err != nil {
        panic(errors.New("Sortutako RSA gako pribatua baliogabea da: " + err.Error()))
    }

    // Gako pribatua x509 formatuan kodifikatu
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

    // PEM blokea sortu
    privateKeyPEM := pem.EncodeToMemory(&pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privateKeyBytes,
    })

    return string(privateKeyPEM)
}