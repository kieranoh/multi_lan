package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the provided data using AES in CBC mode with the provided key.
// It returns the encrypted data, the initialization vector (IV), and the AES key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Check if the key length is valid for AES
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length is too short for AES")
	}

	// Use a 16-byte prefix for AES key
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
	data = pad(data, aes.BlockSize)

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad pads the input data with PKCS7 padding
func pad(src []byte, blockSize int) []byte {
	padding := blockSize - len(src)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(src, padtext...)
}