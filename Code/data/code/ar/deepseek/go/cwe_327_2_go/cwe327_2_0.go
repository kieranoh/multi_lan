package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// اختيار خوارزمية AES فقط (مطلوب 16، 24، أو 32 بايت للمفتاح)
	// نستخدم أول 32 بايت من المفتاح المقدم لمفتاح AES-256
	const aesKeySize = 32 // AES-256
	
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES-256")
	}
	
	// استخراج أول aesKeySize بايت كمفتاح AES
	aesKey := make([]byte, aesKeySize)
	copy(aesKey, key[:aesKeySize])
	
	// إنشاء كتلة AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}
	
	// إنشاء IV (متجه التهيئة)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}
	
	// إعداد وضع CBC
	mode := cipher.NewCBCEncrypter(block, iv)
	
	// إضافة padding للبيانات لتكون مضاعفة لحجم الكتلة
	paddedData := pkcs7Pad(data, aes.BlockSize)
	
	// تشفير البيانات
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey, nil
}

// دالة مساعدة لإضافة padding باستخدام PKCS7
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}