package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"log"
)

// CreatePrivateKey özel bir RSA anahtarı oluşturur, PEM formatında dışa aktarır ve bir dize olarak döndürür.
func CreatePrivateKey() string {
	// 2048 bitlik bir RSA anahtarı oluştur
	privKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("Anahtar oluşturulurken hata oluştu: %v", err)
	}

	// Anahtarı PEM formatına dönüştür
	privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
	privKeyPEM := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privKeyBytes,
	}

	// PEM formatındaki anahtarı bir dizeye yazdır
	var pemData []byte
	pemData = pem.EncodeToMemory(privKeyPEM)

	return string(pemData)
}