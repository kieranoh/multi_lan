package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode with the provided key.
// It returns the encrypted data, initialization vector (IV), and the AES key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Ensure the key is at least 16 bytes for AES
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long for AES")
	}

	// Use the first 16 bytes of the key for AES
	aesKey := key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	paddedData := padData(data, aes.BlockSize)

	// Create a new CBC encrypter
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData := make([]byte, len(paddedData))
	cbc.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padData adds PKCS7 padding to the input data
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	pad := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, pad...)
}