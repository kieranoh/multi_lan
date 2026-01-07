package main

import (
    "crypto/rand"
    "crypto/rsa"
    "encoding/pem"
    "fmt"
)

func CreatePrivateKey() string {
    // RSA 키 ni lazima iwe na ukubwa wa angalau 2048 bits
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        fmt.Println("Error generating key:", err)
        return ""
    }

    // Weka funguo katika muundo wa PEM
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
    pemBlock := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privateKeyBytes,
    }

    // Bado private key katika PEM format kama string
    var privateKeyPEM bytes.Buffer
    if err := pem.Encode(&privateKeyPEM, pemBlock); err != nil {
        fmt.Println("Error encoding key:", err)
        return ""
    }

    return privateKeyPEM.String()
}