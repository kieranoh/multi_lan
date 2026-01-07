package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"fmt"
)

func CreatePrivateKey() string {
	// Генерация закрытого ключа RSA
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		fmt.Println("Ошибка генерации ключа:", err)
		return ""
	}

	// Экспорт закрытого ключа в формате PEM
	privASN1 := privateKey.PrivateKey
	privBytes := x509.MarshalPKCS1PrivateKey(privASN1)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}

	// Кодирование в строку
	var pemBuffer bytes.Buffer
	if err := pem.Encode(&pemBuffer, pemBlock); err != nil {
		fmt.Println("Ошибка кодирования PEM:", err)
		return ""
	}

	return pemBuffer.String()
}