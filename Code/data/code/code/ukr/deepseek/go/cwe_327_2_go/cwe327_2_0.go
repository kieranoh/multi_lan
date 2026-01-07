package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Validate input parameters
	if len(key) == 0 {
		return nil, nil, nil, errors.New("key cannot be empty")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// Use first 32 bytes of key for AES-256 (32 bytes = 256 bits)
	const aesKeyLength = 32
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("key is too short for AES-256")
	}
	aesKey := key[:aesKeyLength]

	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate random IV (16 bytes for AES block size)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data to be multiple of block size
	paddedData := padData(data, aes.BlockSize)

	// Create CBC encryptor
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padData adds PKCS#7 padding to the data
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}