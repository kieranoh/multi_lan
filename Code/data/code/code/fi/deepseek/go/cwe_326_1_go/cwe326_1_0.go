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

// DSAPrivateKey edustaa ASN.1-rakennetta DSA-yksityisavaimelle
type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Generoi yksityinen DSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
func create_private_key_dsa() string {
    // Määritellään DSA-parametrit
    params := &dsa.Parameters{}
    
    // Generoidaan DSA-parametrit
    // Huomaa: DSA.L1024N160 on vanhentunut, mutta käytetään esimerkkinä
    err := dsa.GenerateParameters(params, rand.Reader, dsa.L1024N160)
    if err != nil {
        return fmt.Sprintf("Virhe parametrien generoinnissa: %v", err)
    }
    
    // Luodaan uusi DSA-yksityisavain
    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    
    // Generoidaan yksityinen avain
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        return fmt.Sprintf("Virhe avaimen generoinnissa: %v", err)
    }
    
    // Muodostetaan DSAPrivateKey rakenne
    dsaPrivateKey := DSAPrivateKey{
        Version: 0,
        P:       privateKey.P,
        Q:       privateKey.Q,
        G:       privateKey.G,
        Y:       privateKey.Y,
        X:       privateKey.X,
    }
    
    // Serialisoidaan ASN.1-muotoon
    asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
    if err != nil {
        return fmt.Sprintf("Virhe ASN.1-marshaloinnissa: %v", err)
    }
    
    // Luodaan PEM-lohko
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: asn1Bytes,
    }
    
    // Enkoodataan PEM-muotoon
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    return string(pemBytes)
}