package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// It returns the encrypted data, the IV used for encryption, and the AES key.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Check if the key is at least 16 bytes for AES
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes for AES")
	}

	// Use the first 16 bytes of the key for AES
	aesKey := key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a random IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be multiple of block size
	pad := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, byte(pad))
	for i := 1; i < pad; i++ {
		paddedData = append(paddedData, byte(pad))
	}

	// Encrypt the data
	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey, nil
}