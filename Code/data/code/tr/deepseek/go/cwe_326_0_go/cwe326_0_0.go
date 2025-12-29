package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// CreatePrivateKey özel bir RSA anahtarı oluşturur, PEM formatında dışa aktarır ve bir dize olarak döndürür.
func CreatePrivateKey() string {
	// 2048 bit uzunluğunda RSA anahtarı oluştur
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Hata durumunda nazik bir mesaj döndür
		return fmt.Sprintf("Anahtar oluşturulurken hata oluştu: %v", err)
	}

	// Özel anahtarı PKCS#1 ASN.1 DER formatına dönüştür
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// PEM bloğu oluştur
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// PEM formatına kodla
	pemBytes := pem.EncodeToMemory(privateKeyPEM)
	if pemBytes == nil {
		return "PEM kodlaması başarısız oldu"
	}

	// Dize olarak döndür
	return string(pemBytes)
}