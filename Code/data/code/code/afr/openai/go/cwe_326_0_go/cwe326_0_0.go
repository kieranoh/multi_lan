package main

import (
    "crypto/rand"
    "crypto/rsa"
    "encoding/pem"
    "errors"
    "fmt"
)

func CreatePrivateKey() string {
    // RSA 키 생성
    privKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        return fmt.Sprintf("Error generating key: %v", err)
    }

    // PEM 형식으로 인코딩
    privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)

    pemBlock := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privKeyBytes,
    }

    var pemData []byte
    pemData = pem.EncodeToMemory(pemBlock)

    return string(pemData)
}