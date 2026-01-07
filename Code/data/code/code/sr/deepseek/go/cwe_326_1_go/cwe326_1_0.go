package main

import (
    "crypto/dsa"
    "crypto/rand"
    "encoding/asn1"
    "encoding/pem"
    "errors"
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

// Generišite privatni DSA ključ, eksportujte ga koristeći PEM format i vratite ga kao string.
func create_private_key_dsa() string {
    // Definišite DSA parametre
    params := &dsa.Parameters{}
    
    // Generišite parametre za DSA sa L=2048 i N=256 (preporučene vrednosti)
    // L je dužina ključa u bitovima, N je dužina Q u bitovima
    err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
    if err != nil {
        panic(fmt.Sprintf("Greška pri generisanju DSA parametara: %v", err))
    }
    
    // Generišite privatni ključ sa parametrima
    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        panic(fmt.Sprintf("Greška pri generisanju DSA ključa: %v", err))
    }
    
    // Kreirajte DSAPrivateKey strukturu za ASN.1 kodiranje
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
        panic(fmt.Sprintf("Greška pri ASN.1 kodiranju: %v", err))
    }
    
    // Kreirajte PEM blok
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: asn1Bytes,
    }
    
    // Kodirajte u PEM format
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    return string(pemBytes)
}