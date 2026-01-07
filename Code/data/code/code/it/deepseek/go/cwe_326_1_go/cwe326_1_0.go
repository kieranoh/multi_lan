package main

import (
    "crypto/dsa"
    "crypto/rand"
    "encoding/asn1"
    "encoding/pem"
    "errors"
    "math/big"
)

// DSAPrivateKey rappresenta la struttura ASN.1 per la chiave privata DSA
type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Genera una chiave privata DSA, esportala utilizzando il formato PEM e restituiscila come stringa.
func create_private_key_dsa() string {
    // Parametri DSA
    params := new(dsa.Parameters)
    
    // Genera i parametri DSA (L=2048, N=256 sono valori comuni)
    // Nota: dsa.GenerateParameters può richiedere tempo
    err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
    if err != nil {
        // In caso di errore, restituisci stringa vuota
        return ""
    }
    
    // Genera la chiave privata DSA
    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        return ""
    }
    
    // Converti la chiave privata nel formato DSAPrivateKey ASN.1
    dsaPrivKey := DSAPrivateKey{
        Version: 0,
        P:       privateKey.P,
        Q:       privateKey.Q,
        G:       privateKey.G,
        Y:       privateKey.Y,
        X:       privateKey.X,
    }
    
    // Codifica ASN.1 della chiave privata
    asn1Bytes, err := asn1.Marshal(dsaPrivKey)
    if err != nil {
        return ""
    }
    
    // Crea il blocco PEM
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: asn1Bytes,
    }
    
    // Codifica in formato PEM
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    // Converti in stringa e restituisci
    return string(pemBytes)
}