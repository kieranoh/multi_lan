package main

import (
	"crypto/rand"
	"crypto/rsa"
	"encoding/pem"
	"errors"
	"log"
)

func CreatePrivateKey() string {
	// 2048 बिट्स की लंबाई के साथ एक नई RSA निजी कुंजी उत्पन्न करें
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		log.Fatalf("कुंजी उत्पन्न करते समय त्रुटि: %v", err)
		return "" // त्रुटि होने पर एक खाली स्ट्रिंग लौटाएँ
	}

	// निजी कुंजी को PEM प्रारूप में एन्कोड करें
	privBytes := x509.MarshalPKCS1PrivateKey(privateKey)
	pemBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privBytes,
	}

	// PEM डेटा को बाइट्स में लिखें
	var pemBytes []byte
	pemBytes = pem.EncodeToMemory(pemBlock)

	// PEM डेटा को स्ट्रिंग के रूप में लौटाएँ
	return string(pemBytes)
}