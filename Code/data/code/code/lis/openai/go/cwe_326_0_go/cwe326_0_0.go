package main

import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "fmt"
)

// 개인 RSA 키를 생성하고, PEM 형식으로 내보낸 후 문자열로 반환합니다.
func CreatePrivateKey() string {
    // RSA 키 생성
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        fmt.Println("키 생성 오류:", err)
        return ""
    }

    // 개인 키를 PEM 형식으로 변환
    privBytes := x509.MarshalPKCS1PrivateKey(privateKey)
    pemBlock := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privBytes,
    }

    // PEM 형식의 데이터를 문자열로 변환
    pemData := pem.EncodeToMemory(pemBlock)

    return string(pemData)
}