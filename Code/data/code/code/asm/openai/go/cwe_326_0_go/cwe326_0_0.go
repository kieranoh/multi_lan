package main

import (
    "crypto/rand"
    "crypto/rsa"
    "encoding/pem"
    "fmt"
)

func CreatePrivateKey() string {
    // RSA 키 생성
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        fmt.Println("Error generating RSA key:", err)
        return ""
    }

    // PEM 형식으로 인코딩
    pemBlock := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: x509.MarshalPKCS1PrivateKey(privateKey),
    }

    // PEM 블록을 문자열로 변환
    var pemData bytes.Buffer
    if err := pem.Encode(&pemData, pemBlock); err != nil {
        fmt.Println("Error encoding PEM:", err)
        return ""
    }

    return pemData.String()
}