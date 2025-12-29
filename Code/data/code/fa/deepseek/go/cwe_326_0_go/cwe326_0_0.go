package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
)

// CreatePrivateKey یک کلید خصوصی RSA تولید می‌کند، آن را با فرمت PEM صادر می‌کند و به عنوان یک رشته بازگردانید.
func CreatePrivateKey() string {
	// تولید کلید خصوصی RSA با 2048 بیت
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// در صورت خطا، رشته خالی بازگردانده می‌شود
		return ""
	}

	// تبدیل کلید خصوصی به فرمت DER
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// ایجاد بلوک PEM
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// کدگذاری کلید خصوصی به فرمت PEM
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	// بازگرداندن به عنوان رشته
	return string(privateKeyPEM)
}