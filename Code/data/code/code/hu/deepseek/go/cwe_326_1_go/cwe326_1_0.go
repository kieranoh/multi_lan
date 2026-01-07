package main

import (
    "crypto/dsa"
    "crypto/rand"
    "crypto/x509"
    "encoding/asn1"
    "encoding/pem"
    "fmt"
    "math/big"
)

// A DSAPrivateKey az ASN.1 struktúrát képviseli a DSA privát kulcs számára
type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Generálj egy privát DSA kulcsot, exportáld PEM formátumban, és térj vissza vele stringként.
func create_private_key_dsa() string {
    // DSA paraméterek inicializálása
    params := &dsa.Parameters{}
    
    // L paraméter (kulcshossz) - 1024 bit a biztonságos DSA-hoz
    // Megjegyzés: A DSA 1024 bites kulcsokat használ, de a modern alkalmazásokban
    // érdemes lehet nagyobb méretet használni (2048 bit)
    err := dsa.GenerateParameters(params, rand.Reader, dsa.L1024N160)
    if err != nil {
        return fmt.Sprintf("Hiba a paraméterek generálásakor: %v", err)
    }
    
    // Privát kulcs generálása
    privateKey := &dsa.PrivateKey{
        PublicKey: dsa.PublicKey{
            Parameters: *params,
        },
    }
    
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        return fmt.Sprintf("Hiba a kulcs generálásakor: %v", err)
    }
    
    // A kulcs exportálása ASN.1 formátumba
    dsaPrivateKey := DSAPrivateKey{
        Version: 0,
        P:       privateKey.P,
        Q:       privateKey.Q,
        G:       privateKey.G,
        Y:       privateKey.Y,
        X:       privateKey.X,
    }
    
    // ASN.1 kódolás
    asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
    if err != nil {
        return fmt.Sprintf("Hiba az ASN.1 kódolásnál: %v", err)
    }
    
    // PEM formátum létrehozása
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: asn1Bytes,
    }
    
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    return string(pemBytes)
}