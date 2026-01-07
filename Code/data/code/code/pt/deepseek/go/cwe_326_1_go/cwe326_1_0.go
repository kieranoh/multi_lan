package main

import (
    "crypto/dsa"
    "crypto/rand"
    "encoding/asn1"
    "encoding/pem"
    "fmt"
    "math/big"
)

// DSAPrivateKey representa a estrutura ASN.1 para a chave privada DSA
type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Gere uma chave privada DSA, exporte-a usando o formato PEM e retorne-a como uma string.
func create_private_key_dsa() string {
    // Gerar parâmetros DSA
    params := &dsa.Parameters{}
    
    // Nota: dsa.GenerateParameters foi depreciado em favor de crypto/rand
    // Usaremos GenerateKey que gera tanto parâmetros quanto chave
    var privateKey dsa.PrivateKey
    
    // Tamanho da chave: L=2048, N=256 (recomendado para segurança moderna)
    // DSA permite combinações específicas: (L=1024, N=160), (L=2048, N=224), (L=2048, N=256), (L=3072, N=256)
    err := dsa.GenerateKey(&privateKey, rand.Reader)
    if err != nil {
        return fmt.Sprintf("Erro ao gerar chave DSA: %v", err)
    }
    
    // Criar estrutura ASN.1 DSAPrivateKey
    dsaPrivKey := DSAPrivateKey{
        Version: 0, // Versão 0 conforme RFC 3279
        P:       privateKey.P,
        Q:       privateKey.Q,
        G:       privateKey.G,
        Y:       privateKey.Y,
        X:       privateKey.X,
    }
    
    // Codificar para ASN.1 DER
    derBytes, err := asn1.Marshal(dsaPrivKey)
    if err != nil {
        return fmt.Sprintf("Erro ao codificar chave DSA: %v", err)
    }
    
    // Criar bloco PEM
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: derBytes,
    }
    
    // Codificar para formato PEM
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    return string(pemBytes)
}