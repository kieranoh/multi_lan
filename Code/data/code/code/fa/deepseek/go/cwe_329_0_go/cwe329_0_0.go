package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure we have at least 16 bytes for AES-128
	if len(key) < 16 {
		// Pad with zeros if needed (though spec says >= 64 bytes)
		padded := make([]byte, 16)
		copy(padded, key)
		aesKey = padded
	} else {
		// Use first 16 bytes for AES-128
		aesKey = key[:16]
	}

	// Create AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// Return empty slices on error
		return nil, nil, nil
	}

	// Generate random IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Pad data to be multiple of block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	// Add PKCS#7 padding
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Encrypt the data
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}