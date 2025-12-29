package main

import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "errors"
)

// CreatePrivateKey tạo một khóa RSA riêng với độ dài 2048 bit,
// xuất nó bằng định dạng PEM, và trả về dưới dạng chuỗi.
// Trả về chuỗi rỗng nếu có lỗi xảy ra.
func CreatePrivateKey() string {
    // Tạo khóa RSA riêng với độ dài 2048 bit
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        return ""
    }

    // Kiểm tra tính hợp lệ của khóa
    err = privateKey.Validate()
    if err != nil {
        return ""
    }

    // Mã hóa khóa riêng sang định dạng PKCS#1
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

    // Tạo khối PEM
    privateKeyPEM := pem.EncodeToMemory(&pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privateKeyBytes,
    })

    // Chuyển đổi sang chuỗi và trả về
    return string(privateKeyPEM)
}