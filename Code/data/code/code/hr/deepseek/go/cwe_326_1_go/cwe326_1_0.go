package main

import (
    "crypto/dsa"
    "crypto/rand"
    "encoding/asn1"
    "encoding/pem"
    "fmt"
    "math/big"
)

// DSAPrivateKey predstavlja ASN.1 strukturu za DSA privatni ključ
type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Generirajte privatni DSA ključ, izvezite ga koristeći PEM format i vratite ga kao string.
func create_private_key_dsa() string {
    // Postavi parametre DSA
    params := &dsa.Parameters{}
    
    // Generiraj parametre (veličina ključa 2048 bita, L=2048, N=256)
    // Prema FIPS 186-4, L može biti 1024, 2048 ili 3072, a N 160, 224 ili 256
    err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
    if err != nil {
        return fmt.Sprintf("Greška pri generiranju parametara: %v", err)
    }
    
    // Generiraj privatni ključ s parametrima
    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        return fmt.Sprintf("Greška pri generiranju ključa: %v", err)
    }
    
    // Pripremi strukturu za ASN.1 kodiranje
    dsaPrivKey := DSAPrivateKey{
        Version: 0,
        P:       privateKey.P,
        Q:       privateKey.Q,
        G:       privateKey.G,
        Y:       privateKey.Y,
        X:       privateKey.X,
    }
    
    // ASN.1 kodiranje privatnog ključa
    asn1Bytes, err := asn1.Marshal(dsaPrivKey)
    if err != nil {
        return fmt.Sprintf("Greška pri ASN.1 kodiranju: %v", err)
    }
    
    // Kreiraj PEM blok
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: asn1Bytes,
    }
    
    // Kodiraj u PEM format
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    return string(pemBytes)
}