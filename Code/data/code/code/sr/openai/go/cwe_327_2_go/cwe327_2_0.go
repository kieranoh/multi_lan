package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the data using AES in CBC mode with the provided key.
// The function returns the encrypted data, the initialization vector (IV), and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Ensure the key is at least 32 bytes for AES-256
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key length must be at least 32 bytes for AES-256")
	}

	// Use the first 32 bytes of the key for AES-256
	aesKey := key[:32]

	// Generate a new initialization vector (IV)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Encrypt the data using CBC mode
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(padtext))
	mode.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey, nil
}