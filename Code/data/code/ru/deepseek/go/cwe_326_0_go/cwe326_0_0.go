package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey генерирует закрытый ключ RSA, экспортирует его в формате PEM и возвращает его в виде строки.
func CreatePrivateKey() string {
	// Генерируем закрытый ключ RSA с размером 2048 бит
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// В случае ошибки возвращаем пустую строку
		return ""
	}

	// Преобразуем закрытый ключ в формат PKCS#1
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// Создаем PEM-блок с типом "RSA PRIVATE KEY"
	privateKeyPEM := pem.EncodeToMemory(&pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	})

	// Преобразуем байты в строку и возвращаем
	return string(privateKeyPEM)
}