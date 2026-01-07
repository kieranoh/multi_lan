package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// استخدم أول 32 بايت من المفتاح كمفتاح AES-256
	keyLength := 32 // AES-256 يتطلب 32 بايت (256 بت)
	if len(key) < keyLength {
		// إذا كان المفتاح أقصر من المطلوب، كرره لملء الطول
		extendedKey := make([]byte, keyLength)
		for i := 0; i < keyLength; i++ {
			extendedKey[i] = key[i%len(key)]
		}
		aesKey = extendedKey
	} else {
		aesKey = key[:keyLength]
	}

	// إنشاء كتلة AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// إنشاء IV (متجه التهيئة)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// إضافة padding للبيانات لتكون مضاعفة لحجم الكتلة
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// تشفير البيانات باستخدام وضع CBC
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}