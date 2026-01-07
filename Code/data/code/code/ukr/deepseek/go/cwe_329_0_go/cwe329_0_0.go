package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256 requires 32 bytes key
	keyLength := 32
	if len(key) < keyLength {
		// If key is too short, pad with zeros (though documentation says key is >= 64 bytes)
		paddedKey := make([]byte, keyLength)
		copy(paddedKey, key)
		aesKey = paddedKey
	} else {
		// Use first 32 bytes of the provided key
		aesKey = key[:keyLength]
	}

	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// Return empty slices on error
		return nil, nil, nil
	}

	// Generate random IV (16 bytes for AES)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Create CBC encryptor
	mode := cipher.NewCBCEncrypter(block, iv)

	// Pad data to be multiple of block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	// Add PKCS#7 padding
	for i := 0; i < padding; i++ {
		paddedData[len(data)+i] = byte(padding)
	}

	// Encrypt the data
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}