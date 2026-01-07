package main

import (
    "crypto/rand"
    "crypto/rsa"
    "encoding/pem"
    "errors"
)

func CreatePrivateKey() string {
    // RSA 키 생성
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        return ""
    }

    // PEM 형식으로 인코딩
    privKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
    pemBlock := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privKeyBytes,
    }

    // PEM 블록을 문자열로 변환
    var privateKeyPEM []byte
    privateKeyPEM = pem.EncodeToMemory(pemBlock)

    return string(privateKeyPEM)
}