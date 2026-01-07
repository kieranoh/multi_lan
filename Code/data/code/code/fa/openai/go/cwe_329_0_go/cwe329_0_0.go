package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData رمزگذاری داده‌ها با کلید با استفاده از AES و حالت CBC.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// استفاده از پیشوند کلید برای ایجاد کلید AES
	aesKey = key[:16] // استفاده از 16 بایت اول به عنوان کلید AES

	// ایجاد IV تصادفی
	iv = make([]byte, aes.BlockSize)
	if _, err = io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// ایجاد یک بلاک جدید AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// پر کردن داده‌ها به اندازه متناسب با بلاک
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// رمزگذاری داده‌ها
	encryptedData = make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}