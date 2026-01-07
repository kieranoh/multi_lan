package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// قم بإنشاء مفتاح RSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة.
func CreatePrivateKey() string {
	// إنشاء مفتاح RSA خاص بحجم 2048 بت
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// في حالة حدوث خطأ، نعيد سلسلة فارغة
		return ""
	}

	// تحويل المفتاح الخاص إلى تنسيق PKCS#1 DER
	privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

	// إنشاء كتلة PEM
	privateKeyPEM := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyBytes,
	}

	// ترميز كتلة PEM إلى سلسلة
	privateKeyString := string(pem.EncodeToMemory(privateKeyPEM))

	return privateKeyString
}