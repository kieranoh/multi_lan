package main

import (
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "log"
)

// CreatePrivateKey genera una clau RSA privada, exporta-la utilitzant el format PEM i retorna-la com una cadena.
func CreatePrivateKey() string {
    // Generar la clau RSA
    privKey, err := rsa.GenerateKey(rsa.NewPRNG(), 2048)
    if err != nil {
        log.Fatalf("Error generant la clau RSA: %v", err)
    }

    // Exportar la clau a format PEM
    privKeyDER := x509.MarshalPKCS1PrivateKey(privKey)
    block := pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privKeyDER,
    }

    // Retornar la clau com una cadena
    pemData := pem.EncodeToMemory(&block)
    return string(pemData)
}